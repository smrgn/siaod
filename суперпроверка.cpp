// Проверка на введение целочисленного значения, а не какого-то другого элемента


#include <iostream>
using namespace std;

int Inputint(int m, int M) {
    for (;;) {
        float valuea;
        cout << "Введите число. \n";
        if ((cin >> valuea).good() && (m <= valuea) && (valuea <= M) && (floor(valuea) == valuea)) {
            return valuea;
            break;
        }
        if (cin.fail()) {
            cin.clear();
            cout << "Неверный ввод, повторите. \n";

        }
        else {
            cout << "Число вне допустимого диапазона значений. Повторите ввод. \n";

        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    }
}