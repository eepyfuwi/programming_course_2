#include <iostream>
using namespace std;
// Lab 11
// TODO: реализуйте решение по заданию в labs/lab11_io/README.md
//
// Рекомендация по выводу:
// - без лишнего текста
// - числа через пробел
// - если несколько строк — в фиксированном порядке

int M[3];
int K[3];
int N = 0;

void solve(int);

int main() {
    solve(0);
    cout << N << endl;
    return 0;
}

void solve(int p) {
    if (p == 3) {
        N++;
        for (int i = 0; i < 3; i++) cout << M[i] << endl;
        cout << "--" << endl;
        return;
    }

    for (int i = 0; i < 3; i++) {
        if (!K[i]) {
            M[p] = i + 1;
            K[i] = 1;
            solve(p + 1);
            K[i] = 0;
        }
    }
}