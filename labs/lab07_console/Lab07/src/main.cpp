#include <iostream>
#include <cstdio>

using namespace std;

// Lab 07
// TODO: реализуйте решение по заданию в labs/lab07_console/README.md
//
// Рекомендация по выводу:
// - без лишнего текста
// - числа через пробел
// - если несколько строк — в фиксированном порядке
int main() {
    // Задание 1: вычисление значений функции.
    // Ввод: x0 — начальная точка интервала.
    // TODO: вычислите и выведите 10 значений функции на (0, 4].
    double x0 = 0.0;
    double x;
    double l = 4.0 / 10;
    for (int i = 0; i < 10; i++) {
        x0 = x0 + l;
        x = (sin(x0)) / x0;
        cout << x << endl;
    }
    
    cout << "-----------------------------------" << endl;
    // Задание 2: сумма чисел Фибоначчи.
    // Ввод: MAX — ограничение на сумму.
    // TODO: вычислите N и S (S <= MAX) и выведите результаты.
    long long max_value = 12000;
    long long S = 0;
    int N = 0;
    long long F = 1;
    long long F0 = 0;
    long long F1 = 1;
    while (S <= max_value) {
        S = S + F;
        F = F0 + F1;
        F0 = F1;
        F1 = F;
        N++;
    }

    cout << S << " " << N << endl;
    cout << "-----------------------------------" << endl;
    // Задание 3: Кредит.
    float m, p, sum, per, sumpay;
    float sumper = 0;

    scanf_s("%f %f %f", &sum, &p, &m);
    cout << "-----------------------------------" << endl;
    cout << "   Dolg" << " " << "    Procent" << " " << "   Platezh" << endl;
    cout << "-----------------------------------" << endl;
    float a = 1+ (p/(12*100));
    float mpay = sum / m;
    while (sum > 0) {
        per = sum * a - sum;
        sumpay = mpay + per;
        printf("%.2f %.2f %.2f\n", sum, per, sumpay);
        sum = sum - mpay;
        sumper = sumper + per;
    }
    cout << "-----------------------------------" << endl;
    printf("Vsego procent: %.2f\n", sumper);
    
    
    
    
    return 0;

    
}
