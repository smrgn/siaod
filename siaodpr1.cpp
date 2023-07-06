/*
Задание. Выполнить упражнения по применению битовых операций по
изменению значений битов в ячейке оперативной памяти, созданию маски
для изменения значения ячейки. Создание выражения, содержащего
поразрядные операции, для выполнения определенной операции над
значением ячейки.
*/

#include <iostream>
#include <bitset>
using namespace std;

int exercise1(int x, int m) {
    return x | m;
}

int exercise2(int x, int m) {
    return x & m;
}

int exercise3(int x) {
    return x << 3;
}

int exercise4(int x) {
    return x >> 3;
}

int exercise5(int x, int n, int m) {
    m = m << n;
    return x | m;
}

int main()
{
    setlocale(LC_ALL, "ru");
    int exc = 0;
    int q = 1;
    while (q != 0) {
        cout << "Выберете задание:\n";
        cout << "1 - Установить 1-ый, 6-ой и 9-ый биты в значение 1;\n";
        cout << "2 - Обнулить 1-ый, 6-ой и 9-ый биты;\n";
        cout << "3 - Умножить значение переменной на 8;\n";
        cout << "4 - Разделить значение переменной на 8;\n";
        cout << "5 - Установить n-ый бит в 1, используя маску 1.\n";
        cin >> exc;
        while (exc != 1 && exc != 2 && exc != 3 && exc != 4 && exc != 5) {
            cout << "Вы ввели неверное число. Повторите ввод: ";
            cin >> exc;
        }
        int x, mask, n;   
        x = 0x22D;
        switch (exc) {
        case 1: 
            mask = 0b1001000010;
            cout << "x      = 0b" << bitset<10>(x) << endl;
            cout << "mask   = 0b" << bitset<10>(mask) << endl;
            cout << "x|mask = 0b" << bitset<10>(exercise1(x, mask)) << endl;
            cout << "Значение 1-ого, 6-ого и 9-ого битов - 1. Программа работает корректно." << endl;
            break;
        case 2:
            mask = 0b0110111101;
            cout << "x      = 0b" << bitset<10>(x) << endl;
            cout << "mask   = 0b" << bitset<10>(mask) << endl;
            cout << "x&mask = 0b" << bitset<10>(exercise2(x, mask)) << endl;
            cout << "Значение 1-ого, 6-ого и 9-ого битов - 0. Программа работает корректно." << endl;
            break;
        case 3:
            cout << "Введите число в 10 сс: ";
            cin >> x;
            cout << "x0 = 0b" << bitset<10>(x) << "      x0 = " << x << endl;
            x = exercise3(x);
            cout << "x1 = 0b" << bitset<10>(x) << "      x1 = " << x << endl;
            cout << "Значение x увеличилось в 8 раз. Программа работает корректно." << endl;
            break;
        case 4:
            cout << "Введите число в 10 сс: ";
            cin >> x;
            cout << "x0 = 0b" << bitset<10>(x) << "      x0 = " << x << endl;
            x = exercise4(x);
            cout << "x1 = 0b" << bitset<10>(x) << "      x1 = " << x << endl;
            cout << "Значение x уменьшилось в 8 раз. Программа работает корректно." << endl;
            break;
        case 5:
            cout << "Введите число в 10 сс: ";
            cin >> x;
            cout << "Введите номер биты, который вы хотите установить в 1: ";
            cin >> n;
            mask = 0b0000000001;
            cout << "x0 = 0b" << bitset<10>(x) << endl;
            cout << "x1 = 0b" << bitset<10>(exercise5(x, n, mask)) << endl;
            cout << "Значение " << n << "-ого бита - 1. Программа работает корректно." << endl;
            break;
        }
        cout << "Введите 0, если хотите выйти из программы, или любое другое число, чтобы продолжить: ";
        cin >> q;
    }
}
