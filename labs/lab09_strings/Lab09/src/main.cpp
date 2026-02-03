#include <iostream>
#include <string>
#include <vector>

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

    // Упражнение 4: ввод количества слов и самих слов.
    int word_count = 0;
    if (!(std::cin >> word_count)) {
        return 0;
    }

    std::vector<std::string> words;
    words.reserve(word_count);
    for (int i = 0; i < word_count; ++i) {
        std::string word;
        std::cin >> word;
        words.push_back(word);
    }

    // TODO: выведите слова с четными номерами (2, 4, 6, ...), по одному в строке.
    return 0;
}
