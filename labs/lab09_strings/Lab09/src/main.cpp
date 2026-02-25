#include <iostream>
#include <string>
#include <vector>
using namespace std;
// Lab 09
// TODO: реализуйте решение по заданию в labs/lab09_strings/README.md
//
// Рекомендация по выводу:
// - без лишнего текста
// - числа через пробел
// - если несколько строк — в фиксированном порядке
int main() {
    // Упражнения 1–3: демонстрация/анализ строковых функций (без ввода).
    // TODO: добавьте примеры и вывод результатов.
    const char* str1 = "pizza", *str2 = "cola";
    int n = strlen(str1);
    if (strcmp(str1, str2) != 0)
        cout << "-" << endl;
    else cout << "+" << endl;
    
    if (strchr(str1, 'i')) cout << "i" << endl;
    cout << str1 << " " << str2 << " " << n << endl;

    string s1 = "burger", s2 = "pasta";
    s2.clear();
    if (s2.empty()) s2.append("asta");
    else s1.erase(2, 2);
    cout << s1 << " " << s2 << endl;
    // Упражнение 4: ввод количества слов и самих слов.
    char** str_ar;
    int nt;
    cin >> nt;
    str_ar = new char* [nt];
    for (int i = 0; i < nt; i++) {
        str_ar[i] = new char[10];
        cin >> str_ar[i];
    }

    for (int i = 0; i < nt; i++) {
        if (i%2!=0)
        cout << i + 1 << ": " << str_ar[i] << endl;
    }
    // TODO: выведите слова с четными номерами (2, 4, 6, ...), по одному в строке.
    return 0;
}
