#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
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
        for (int j = 0; j < n+1; j++) {
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

int solveSystem(double** mat, int m, int n, double* x, double eps = 1e-9) {
    
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
        for (int j = col; j < n+1; j++) {
            matrix[currentRow][j] /= base;
        }

        //обнуление остальных строк
        for (int row = 0; row < m; row++) {
            if (row != currentRow && fabs(matrix[row][col]) > eps) {
                double factor = matrix[row][col];
                for (int j = col; j < n+1; j++) {
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
            ofstream resultFile("C:\\Users\\donik\\source\\repos\\programming_course_2\\labs\\lab13_linear_algebra\\Lab13\\src\\result.txt");
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

        ofstream resultFile("C:\\Users\\donik\\source\\repos\\programming_course_2\\labs\\lab13_linear_algebra\\Lab13\\src\\result.txt");
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

        ofstream resultFile("C:\\Users\\donik\\source\\repos\\programming_course_2\\labs\\lab13_linear_algebra\\Lab13\\src\\result.txt");
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
    double** matrix = nullptr;

    if (readMatrixFromFile("C:\\Users\\donik\\source\\repos\\programming_course_2\\labs\\lab13_linear_algebra\\Lab13\\src\\system.txt", m, n, matrix)) {
        cout << "\n=== file prochitan ===" << endl;
        cout << "(M): " << m << endl;
        cout << "(N): " << n << endl;

        double* x = new double[n];
        int result = solveSystem(matrix, m, n, x);
        delete[] x;
        freeMatrix(matrix, m);
    }
    else {
        cerr << "ne udalos procitat file" << endl;
    }

    return 0;
}