#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <format>
#include <matplot/matplot.h>
#include <sstream>

using namespace matplot;
using namespace std;
// Lab 13
// TODO: реализуйте решение по заданию в labs/lab13_linear_algebra/README.md
//
// Рекомендация по выводу:
// - без лишнего текста
// - числа через пробел
// - если несколько строк — в фиксированном порядке

double** allocateMatrix(int rows, int cols) {
    double** matrix = new double* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
    }
    return matrix;
}

void freeMatrix(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void printMatrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%10.2f ", matrix[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}

bool readMatrixFromFile(const string& filename, int& m, int& n, double**& matrix) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "ne udalos otkrit file " << filename << endl;
        return false;
    }

    // читаем количество уравнений и неизвестных
    file >> m >> n;

    if (m <= 0 || n <= 0) {
        cerr << "wrong razmeri (m=" << m << ", n=" << n << ")" << endl;
        file.close();
        return false;
    }

    // выделяем память под расширенную матрицу (m строк, n+1 столбцов)
    matrix = allocateMatrix(m, n + 1);

    // читаем коэффициенты и свободные члены
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n + 1; j++) {
            if (!(file >> matrix[i][j])) {
                cerr << "nedostatocho dannih " << i + 1 << endl;
                freeMatrix(matrix, m);
                matrix = nullptr;
                file.close();
                return false;
            }
        }
    }

    file.close();
    return true;
}

int solveSystem(double** mat, int m, int n, double* x, int z, double eps = 1e-9) {

    //копирование матрицы
    double** matrix = allocateMatrix(m, n + 1);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n + 1; j++) {
            matrix[i][j] = mat[i][j];
        }
    }

    cout << "ishod matrix " << m << "x" << n + 1 << ":\n";
    printMatrix(matrix, m, n + 1);

    int rank = 0;
    int currentRow = 0;
    int* baseCols = new int[n];
    for (int i = 0; i < n; i++) baseCols[i] = -1;

    //поиск главного элемента
    for (int col = 0; col < n && currentRow < m; col++) {
        int maxRow = currentRow;
        double maxValue = fabs(matrix[currentRow][col]);

        for (int row = currentRow + 1; row < m; row++) {
            if (fabs(matrix[row][col]) > maxValue) {
                maxValue = fabs(matrix[row][col]);
                maxRow = row;
            }
        }

        if (maxValue < eps) {
            continue;
        }

        if (maxRow != currentRow) {
            double* temp = matrix[maxRow];
            matrix[maxRow] = matrix[currentRow];
            matrix[currentRow] = temp;
            cout << "perestanovka strok " << currentRow << " <-> " << maxRow << endl;
        }

        //нормализация ведущей строки
        double base = matrix[currentRow][col];
        for (int j = col; j < n + 1; j++) {
            matrix[currentRow][j] /= base;
        }

        //обнуление остальных строк
        for (int row = 0; row < m; row++) {
            if (row != currentRow && fabs(matrix[row][col]) > eps) {
                double factor = matrix[row][col];
                for (int j = col; j < n + 1; j++) {
                    matrix[row][j] -= factor * matrix[currentRow][j];
                }
            }
        }

        baseCols[rank] = col;
        rank++;
        currentRow++;

        cout << "posle obrabotki " << col << " (rank = " << rank << "):\n";
        printMatrix(matrix, m, n + 1);
    }

    //проверка на совместность
    for (int i = 0; i < m; i++) {
        bool allZeros = true;
        for (int j = 0; j < n; j++) {
            if (fabs(matrix[i][j]) > eps) {
                allZeros = false;
                break;
            }
        }
        if (allZeros && fabs(matrix[i][n]) > eps) {
            cout << "nesovmestna row " << i << ": all coefs = 0, but result = " << matrix[i][n] << endl;
            ofstream resultFile(format("C:\\Users\\donik\\source\\repos\\CMakeProject2\\result{}.txt",z));
            if (resultFile.is_open()) {
                resultFile << "no solutions\n";
                resultFile.close();
            }
            freeMatrix(matrix, m);
            delete[] baseCols;
            return 1;
        }
    }

    //анализ количества решений

    // only
    if (rank == n) {
        cout << "1 resheni (rank = " << rank << " = " << n << ")\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (fabs(matrix[j][i]) > eps) {
                    x[i] = matrix[j][n];
                    break;
                }
            }
        }

        ofstream resultFile(format("C:\\Users\\donik\\source\\repos\\CMakeProject2\\result{}.txt", z));
        if (resultFile.is_open()) {
            for (int i = 0; i < n; i++) {
                resultFile << x[i];
                if (i < n - 1) resultFile << " ";
            }
            resultFile.close();
        }

        freeMatrix(matrix, m);
        delete[] baseCols;
        return 0;
    }

    // inf 
    else if (rank < n) {
        bool* isBase = new bool[n]();
        for (int i = 0; i < rank; i++) {
            if (baseCols[i] != -1) {
                isBase[baseCols[i]] = true;
            }
        }

        ofstream resultFile(format("C:\\Users\\donik\\source\\repos\\CMakeProject2\\result{}.txt", z));
        if (resultFile.is_open()) {
            // basis
            for (int i = 0; i < rank; i++) {
                int col = baseCols[i];
                resultFile << "x" << col + 1 << " = ";

                for (int row = 0; row < m; row++) {
                    if (fabs(matrix[row][col]) > eps) {
                        resultFile << matrix[row][n];

                        for (int j = 0; j < n; j++) {
                            if (!isBase[j] && fabs(matrix[row][j]) > eps) {
                                double coeff = -matrix[row][j];
                                if (coeff > 0) {
                                    resultFile << " + " << coeff << "*x" << j + 1;
                                }
                                else if (coeff < 0) {
                                    resultFile << " - " << -coeff << "*x" << j + 1;
                                }
                            }
                        }
                        resultFile << "\n";
                        break;
                    }
                }
            }

            // free
            resultFile << "\n";
            for (int j = 0; j < n; j++) {
                if (!isBase[j]) {
                    resultFile << "x" << j + 1 << " free\n";
                }
            }

            resultFile.close();
            cout << "obshee reshene v result.txt\n";
        }
        else {
            cerr << "ne udalos otkrit result.txt\n";
        }

        delete[] isBase;
        freeMatrix(matrix, m);
        delete[] baseCols;
        return 2;
    }

    freeMatrix(matrix, m);
    delete[] baseCols;
    return -1;
}



int main() {
    int m, n;
    int err = 0;
    double** matrix = nullptr;
    
    ifstream inputFile("C:\\Users\\donik\\source\\repos\\CMakeProject2\\system.txt");
    if (!inputFile) {
        cerr << "ne udalos otkrit system.txt" << endl;
        return 1;
    }

    string line1, line2, line3;
    getline(inputFile, line1);
    getline(inputFile, line2);
    getline(inputFile, line3);
    inputFile.close();

    double xp1, yp1, cp1;
    double xp2, yp2, cp2;
    double xp3, yp3, cp3;

    stringstream ss1(line1);
    ss1 >> xp1 >> yp1 >> cp1;
    stringstream ss2(line2);
    ss2>> xp2 >> yp2 >> cp2;
    stringstream ss3(line3);
    ss3 >> xp3 >> yp3 >> cp3;



    ofstream file1("C:\\Users\\donik\\source\\repos\\CMakeProject2\\output1.txt");
    ofstream file2("C:\\Users\\donik\\source\\repos\\CMakeProject2\\output2.txt");
    ofstream file3("C:\\Users\\donik\\source\\repos\\CMakeProject2\\output3.txt");

    file1 << "2 2" << "\n" << line1 << "\n" << line2 << "\n";
    file2 << "2 2" << "\n" << line2 << "\n" << line3 << "\n";
    file3 << "2 2" << "\n" << line1 << "\n" << line3 << "\n";

    file1.close();
    file2.close();
    file3.close();

    
  
    

    for (int i = 1; i < 4; i++) {
        if (readMatrixFromFile(format("C:\\Users\\donik\\source\\repos\\CMakeProject2\\output{}.txt", i), m, n, matrix)) {
            cout << "\n=== file prochitan ===" << endl;
            double* x = new double[n];
            int result = solveSystem(matrix, m, n, x, i);
            delete[] x;
            freeMatrix(matrix, m);
        }
        else {
            cerr << "ne udalos procitat file" << endl;
        }
    }

    ifstream output1("C:\\Users\\donik\\source\\repos\\CMakeProject2\\result1.txt");
    ifstream output2("C:\\Users\\donik\\source\\repos\\CMakeProject2\\result2.txt");
    ifstream output3("C:\\Users\\donik\\source\\repos\\CMakeProject2\\result3.txt");

    double x1, y1;
    double x2, y2;
    double x3, y3;

    if (!(output1 >> x1 >> y1)) {
        cout << "\n===degenerate case===" << endl;
        err = 1;
    }
    if (!(output2 >> x2 >> y2)) {
        cout << "\n===degenerate case===" << endl;
        err = 1;
    }
    if (!(output3 >> x3 >> y3)) {
        cout << "\n===degenerate case===" << endl;
        err = 1;
    }
    cout << "\n" << endl;

    output1.close();
    output2.close();
    output3.close();

    double S;
    if (err == 0)
    {
        S = fabs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2);
        cout << S << endl;
    }
    fimplicit([=](double x, double y) { return xp1 * x + yp1 * y - cp1; }, array<double, 4>{-20, 20, -20, 20})->line_width(2);
    hold(on);
    fimplicit([=](double x, double y) { return xp2 * x + yp2 * y - cp2; }, array<double, 4>{-20, 20, -20, 20})->line_width(2);
    hold(on);
    fimplicit([=](double x, double y) { return xp3 * x + yp3 * y - cp3; }, array<double, 4>{-20, 20, -20, 20})->line_width(2);
    hold(on);
    text(x1, y1, format("({},{})",x1,y1));
    text(x2, y2, format("({},{})", x2, y2));
    text(x3, y3, format("({},{})", x3, y3));
    xlim({ -10,10 });
    ylim({ -10,10 });
    show();
    
    return 0;
}

