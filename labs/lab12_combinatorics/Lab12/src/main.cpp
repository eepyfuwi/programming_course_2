#include <iostream>
using namespace std;
// Lab 12
// TODO: реализуйте решение по заданию в labs/lab12_combinatorics/README.md
//
// Рекомендация по выводу:
// - без лишнего текста
// - числа через пробел
// - если несколько строк — в фиксированном порядке

bool check(int**, int, int, int);
int solve(int**, int, int);

int main() {
    int** M;
    int K,N = 0;
    cin >> K;
    M = new int* [K];
    for (int i = 0; i < K; i++) {
        M[i] = new int[K];
        for (int j = 0; j < K; j++) {
            M[i][j] = 0;
        }
    }
    N = solve(M, 0, K);
    cout << N << endl;
    return 0;
}

bool check(int** M, int r, int c, int K) {
    for (int i = 0; i < r; i++) {
        if (M[i][c] == 1) return false;
    }
    for (int i = r, j = c; i >= 0 && j >= 0; i--, j--) {
        if (M[i][j] == 1) return false;
    }
    for (int i = r, j = c; i >= 0 && j < K; i--, j++) {
        if (M[i][j] == 1) return false;
    }
    return true;
}

int solve(int** M, int r, int K) {
    if (r == K) {
        for (int i = 0; i < K; i++) {
            for (int j = 0; j < K; j++) {
                if (M[i][j] == 1)
                    cout << "Q ";
                else
                    cout << ". "; 
            }
            cout << endl;
        }
        cout << endl;
        return 1;
    }
    int sum = 0;

    for (int j = 0; j < K; j++) {
        if (check(M, r, j, K)) {
            M[r][j] = 1;
            sum += solve(M, r + 1, K);
            M[r][j] = 0;
        }
    }
    return sum;
}
//const int MAX = 100;
//int c[MAX];
//int d1[MAX * 2];
//int d2[MAX * 2];
//int K, N;
//
//void solve(int);
//
//int main() {
//	cin >> K;
//	
//	for (int i = 0; i < K; i++) c[i] = 0;
//	for (int i = 0; i < 2 * K - 1; i++) d1[i] = d2[i] = 0;
//	N = 0;
//	solve(0);
//	cout << N << endl;
//	return 0;
//}
//
//void solve(int r) {
//	if (r == K) {
//		N++; return;
//	}
//	for (int j = 0; j < K; j++) {
//		if (!c[j] && !d1[r - j + K - 1] && !d2[r + j]) {
//			c[j] = d1[r - j + K - 1] = d2[r + j] = 1;
//			solve(r + 1);
//			c[j] = d1[r - j + K - 1] = d2[r + j] = 0;
//		}
//	}
//}