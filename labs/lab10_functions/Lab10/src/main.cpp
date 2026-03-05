#include <iostream>
#include <random>
using namespace std;
// Lab 10
// TODO: реализуйте решение по заданию в labs/lab10_functions/README.md
//
// Рекомендация по выводу:
// - без лишнего текста
// - числа через пробел
// - если несколько строк — в фиксированном порядке

void zapakouka(int[18], int*);
void raspakouka(int[18], int*);


int main() {
    random_device rd;
    mt19937 gen(rd());
    int STARTart[18];
    int N = 0;
    for (int i = 0; i < 18; i++) {

        uniform_int_distribution<> dis_int(60, 500);
        int rd_int = dis_int(gen);
        STARTart[i] = rd_int;
        N += rd_int;
        cout << STARTart[i] << endl;
    }
    int* pSTARTar;
    int* ar = new int[N];
    raspakouka(STARTart, ar);
    cout << "---------------------------------------" << endl;
    int art[18]{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    zapakouka(art, ar);
   
    for (int i = 0; i < 18; i++) {
        cout << art[i] << endl;
    }
    return 0;
}
void zapakouka(int art[18], int* ar) {
    int* par;
    par = ar;
    for (int i = 0; i < 18; i++) while (*par == i && par++) art[i]++;
    return;
}

void raspakouka(int art[18], int* ar) {
    int* par;
    par = ar;
    for (int i = 0; i < 18; i++) {
        for (int l = 0; l < art[i]; l++) {
            *par = i;
            par++;
        }
    }
    return;
}
