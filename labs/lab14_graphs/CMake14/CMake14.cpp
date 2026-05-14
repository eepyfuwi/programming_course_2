// CMake14.cpp: определяет точку входа для приложения.
//

#include "CMake14.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <format>
#include <matplot/matplot.h>
#include <sstream>
using namespace std;
using namespace matplot;

void cdeep(int k, int* S, int* L, int* D, int* C, int q)
{
	int i, j;
	for (i = S[k]; i < S[k] + L[k]; i++)
	{
		j = D[i];
		if (C[j] == 0)
		{
			C[j] = q;
			cdeep(j, S, L, D, C, q);
		}
	}
}

void deep(int k, int n, int** M, int* R, int& nom)
{
	for (int i = 0; i < n; i++) {
		if ((M[k][i] == 1) && (R[i] == 0)) {
			R[i] = nom;
			deep(i, n, M, R, nom);
		}
	}
}


int main()
{
	ifstream file("C:\\Users\\donik\\source\\repos\\programming_course_2\\labs\\lab14_graphs\\CMake14\\in.txt");
	if (!file.is_open()) {
		cerr << "ne udalos otkrit file " << endl;
		return false;
	}
	int m, n;
	file >> n >> m;

	if (m <= 0 || n <= 0) {
		cerr << "wrong razmeri (m=" << m << ", n=" << n << ")" << endl;
		file.close();
		return false;
	}

	int **matrix = new int* [n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = new int[n];
		for (int j = 0; j < n; j++) 
			matrix[i][j] = 0;
	}
	
	for (int i = 0; i < m; i++)
	{
		int u, v;
		file >> u >> v;
		matrix[u][v] = 1; matrix[v][u] = 1;
	}
	file.close();

	ofstream out1("C:\\Users\\donik\\source\\repos\\programming_course_2\\labs\\lab14_graphs\\CMake14\\out1.txt");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			out1 << matrix[i][j] << " ";
		}
		out1 << "\n";
	}
	out1.close();

	int* L = new int[n]();  
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] == 1) {
				L[i]++;
			}
		}
	}

	int* S = new int[n];
	S[0] = 0;
	for (int j = 1; j < n; j++) {
		S[j] = S[j - 1] + L[j - 1];
	}

	int* U = new int[n];
	for (int j = 0; j < n; j++) {
		U[j] = S[j];
	}

	int* D = new int[2*m];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matrix[i][j] == 1) {
				D[U[i]] = j;
				U[i]++;
			}
		}
	}

	ofstream out2("C:\\Users\\donik\\source\\repos\\programming_course_2\\labs\\lab14_graphs\\CMake14\\out2.txt");
	for (int i = 0; i < 2*m; i++) {
		out2 << D[i] << " ";
	}
	out2.close();

	ofstream out3("C:\\Users\\donik\\source\\repos\\programming_course_2\\labs\\lab14_graphs\\CMake14\\out3.txt");
	for (int i = 0; i < n; i++) {
		int j = 0; int k = S[i];
		while (j < L[i]) {
			out3 << i << " " << D[k] << " ";
			j++; k++;
			out3 << "\n";
		}
	}
	out3.close();

	int* C = new int[n]();
	int q = 0;
	for (int i = 0; i < n; i++) {
		if (C[i] == 0) {
			q++;
			C[i] = q;
			cdeep(i, S, L, D, C, q);
		}
	}
	ofstream gen("C:\\Users\\donik\\source\\repos\\programming_course_2\\labs\\lab14_graphs\\CMake14\\gen.txt");
	int sum = 0;
	int d = 0;
	for (int i = 1; i < n + 1; i++) {
		if (d == n) {
			gen << sum;
			break;
		}
		int j = 0;
		while (j < n) {
			if (C[j] == i) {
				gen << j << "-";
				d++;
			}
			j++;
		}
		sum++;
		gen << "\n";
	}
	gen.close();

	int* R = new int[n](); 
	int nom = 0;

	for (int i = 0; i < n; i++) {
		if (R[i] == 0) {
			nom++;
			R[i] = nom;
			deep(i, n, matrix, R, nom);
		}
	}

	ofstream gen2("C:\\Users\\donik\\source\\repos\\programming_course_2\\labs\\lab14_graphs\\CMake14\\gen2.txt");
	int sum2 = 0;
	int d2 = 0;
	for (int i = 1; i < n + 1; i++) {
		if (d2 == n) {
			gen2 << sum2;
			break;
		}
		int j2 = 0;
		while (j2 < n) {
			if (R[j2] == i) {
				gen2 << j2 << "-";
				d2++;
			}
			j2++;
		}
		sum2++;
		gen2 << "\n";
	}
	gen2.close();

	vector<pair<size_t, size_t>> edges;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (matrix[i][j] == 1) {
				edges.push_back({ i, j });
			}
		}
	}
	vector<double> x(n), y(n);
	for (int i = 0; i < n; i++) {
		double angle = 2.0 * 3.14 * i / n;
		x[i] = cos(angle);
		y[i] = sin(angle);
	}
	auto g = graph(edges);
	g->x_data(x);
	g->y_data(y);
	vector<double> colors(n);
	for (int i = 0; i < n; i++) {
		colors[i] = C[i];
	}
	g->marker_colors(colors);
	g->marker_size(15);
	g->line_width(1.5);
	view(2);
	show();

	for (int i = 0; i < n; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
	delete[] L;
	delete[] S;
	delete[] U;
	delete[] D;
	delete[] C;
	delete[] R;
	return 0;
}

