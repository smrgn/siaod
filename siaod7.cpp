/*Разработать алгоритм решения задачи с применением метода указанного
в варианте и реализовать программу.
1) Оценить количество переборов при решении задачи стратегией «в
лоб» - грубой силы
2) Привести анализ снижения числа переборов при применении метода.
Задание.*/

#include <iostream>
#include <vector>

using namespace std;

//функция для вычисления методом динамического программирования
int dinamicProg(int length, int width, vector<vector<int>>& res) {
    //проверка на выход за допустимые границы
    if (length == 0 || width == 0) {
        return 0;
    }
    //проверка наличия уже вычисленного результата
    if (res[length - 1][width - 1] != -1) {
        return res[length - 1][width - 1];
    }
    //при отсутствии вычисленного результата,
    //вычисляем его единожды и запоминаем
    res[length - 1][width - 1] = dinamicProg(length - 1, width, res) + dinamicProg(length, width - 1, res);
    return res[length - 1][width - 1];
}


//функция для вычисления методом "в лоб"
int bruteForce(int length, int width) {
    //проверка на выход за допустимые границы
    if (length == 0 || width == 0) {
        return 0;
    }
    //проверка на нахождение в точке назначения
    if (length == 1 && width == 1) {
        return 1;
    }
    //рекурсивный вызов для шага вправо и шага вниз
    return bruteForce(length - 1, width) + bruteForce(length, width - 1);
}

int main()
{
    //взаимодействие с пользователем и ввод данных
    int length = 0, width = 0;
    cout << "input length\n";
    cin >> length;
    cout << "input width\n";
    cin >> width;
    //создание массива для храниения уже вычисленных значений
    vector<vector<int>> results;
    for (int i = 0; i < length; i++) {
        results.push_back(vector<int>(width, -1));
    }
    //установка дефолтного значения в топ случае, когда мы в точке назначения
    results[0][0] = 1;
    //вывод результата работы
    cout << "amount of possible solutions is " << dinamicProg(length, width, results) << endl;
    //контрольная проверка с помощью метода "в лоб"
    cout << bruteForce(length, width);
}




