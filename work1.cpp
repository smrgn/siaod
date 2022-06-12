#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#define Len 10
using namespace std;

void output(int* arr, int &n) {
    cout << "Массив: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}
void output_vec(vector <int> arr) {
    cout << "Массив: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
}
void put(int &n, int* arr) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
}
void put_vec(vector <int> &arr) { 
    srand(time(NULL));
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = rand() % 100;
    }
}
int order(int* arr, int &n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}
int order_vec(vector <int> &arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}
void change(int* arr_new, int* arr, int& n) {
    for (int i = 0; i < n; i++) {
        arr[i] = arr_new[i];
    }
}
void task2_static(int &n, int* arr) {
    srand(time(NULL));
    int numb, v = 0;
    cout << "Напишите 1, чтобы самостоятельно ввести число, или 0, чтобы ввелось случайное число:\n";
    cin >> v;
    while (v != 1 && v != 0) {
        cout << "Введено некорректное значение. Повторите ввод: \n";
        cin >> v;
    }
    if (v == 1) {
        cout << "Введите число: ";
        cin >> numb;
        while (numb == 0) {
            cout << "Введено некорректное значение. Повторите ввод: \n";
            cin >> numb;
        }
    }
    else {
        numb = (rand() % 10) ;
        while (numb == 0) {
            numb = (rand() % 10);
        }
        cout << "Введенное число: " << numb << endl;
    }
    int arr_new[Len];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % numb != 0) {
            arr_new[j++] = arr[i];
        }
    }
    n = j;
    output(arr_new, n);
    cout << endl;
    change(arr_new, arr, n);
}
void task2_dyn(int &n, int* arr) {
    srand(time(NULL));
    int numb, v = 0;
    cout << "Напишите 1, чтобы самостоятельно ввести число, или 0, чтобы ввелось случайное число:\n";
    cin >> v;
    while (v != 1 && v != 0) {
        cout << "Введено некорректное значение. Повторите ввод: \n";
        cin >> v;
    }
    if (v == 1) {
        cout << "Введите число: ";
        cin >> numb;
        while (numb == 0) {
            cout << "Введено некорректное значение. Повторите ввод: \n";
            cin >> numb;
        }
    }
    else {
        numb = (rand() % 10);
        while (numb == 0) {
            numb = (rand() % 10);
        }
        cout << "Введенное число: " << numb << endl;
    }
    int* arr_new = new int[n];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % numb != 0) {
            arr_new[j++] = arr[i];
        }
    }
    n = j;
    change(arr_new, arr, n);
    output(arr, j);
    cout << endl;
    delete[] arr_new;
}
void task2_vec(vector <int> &arr) {
    srand(time(NULL));
    int numb, v = 0;
    cout << "Напишите 1, чтобы самостоятельно ввести число, или 0, чтобы ввелось случайное число:\n";
    cin >> v;
    while (v != 1 && v != 0) {
        cout << "Введено некорректное значение. Повторите ввод: \n";
        cin >> v;
    }
    if (v == 1) {
        cout << "Введите число: ";
        cin >> numb;
        while (numb == 0) {
            cout << "Введено некорректное значение. Повторите ввод: \n";
            cin >> numb;
        }
    }
    else {
        numb = (rand() % 10);
        while (numb == 0) {
            numb = (rand() % 10);
        }
        cout << "Введенное число: " << numb << endl;
    }
    int j = 0, n = arr.size();
    vector <int> arr_new(n);
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] % numb != 0) {
            arr_new[j++] = arr[i];
        }
    }
    arr_new.resize(j);
    output_vec(arr_new);
    cout << endl;
    arr = arr_new;

}
int task3_static(int &n, int* arr) {
    srand(time(NULL));
    int numb, v = 0;
    if (n == 10) {
        cout << "К сожалению, массив уже заполнен, не получится добавить число.\n";
        return 0;
    }
    else {
        cout << "Напишите 1, чтобы самостоятельно ввести число, или 0, чтобы ввелось случайное число:\n";
        cin >> v;
        while (v != 1 && v != 0) {
            cout << "Введено некорректное значение. Повторите ввод: \n";
            cin >> v;
        }
        if (v == 1) {
            cout << "Введите число: ";
            cin >> numb;
        }
        else {
            numb = rand();
            cout << "Введенное число: " << numb << endl;
        }
        if (numb >= arr[n - 1]) {
            cout << "В массиве отсутсвуют элементы, которые больше введенного\n";
            return 0;
        }
        int arr_new[Len];
        int j = 0, i = 0, flag = 0;
        while (i < n) {
            if (flag == 1 || numb >= arr[i]) {
                arr_new[j++] = arr[i++];
            }
            else {
                arr_new[j++] = numb;
                flag = 1;
            }
        }
        n = j;
        output(arr_new, n);
        cout << endl;
        change(arr_new, arr, n);

    }
}
int task3_dyn(int &n, int* arr) {
    srand(time(NULL));
    int numb, v = 0;
    cout << "Напишите 1, чтобы самостоятельно ввести число, или 0, чтобы ввелось случайное число:\n";
    cin >> v;
    while (v != 1 && v != 0) {
        cout << "Введено некорректное значение. Повторите ввод: \n";
        cin >> v;
    }
    if (v == 1) {
        cout << "Введите число: ";
        cin >> numb;
    }
    else if (v == 0) {
        numb = rand();
        cout << "Введенное число: " << numb << endl;
    }
    if (numb >= arr[n - 1]) {
        cout << "В массиве отсутсвуют элементы, которые больше введенного\n";
        return 0;
    }
    int* arr_new = new int[n + 1];
    int j = 0, i = 0, flag = 0;
    while (i < n) {
        if (flag == 1 || numb >= arr[i]) {
            arr_new[j++] = arr[i++];
        }
        else {
            arr_new[j++] = numb;
            flag = 1;
        }
    }
    n = j;
    output(arr_new, n);
    change(arr_new, arr, n);
    delete[] arr_new;
    cout << endl;
}
int task3_vec(vector <int> &arr) {
    srand(time(NULL));
    int numb, v = 0, n = arr.size();
    cout << "Напишите 1, чтобы самостоятельно ввести число, или 0, чтобы ввелось случайное число:\n";
    cin >> v;
    while (v != 1 && v != 0) {
        cout << "Введено некорректное значение. Повторите ввод: \n";
        cin >> v;
    }
    if (v == 1) {
        cout << "Введите число: ";
        cin >> numb;
    }
    else if (v == 0) {
        numb = rand();
        cout << "Введенное число: " << numb << endl;
    }
    if (numb >= arr[n - 1]) {
        cout << "В массиве отсутсвуют элементы, которые больше введенного\n";
        return 0;
    }
    vector <int> arr_new(n + 1);
    int j = 0, i = 0, flag = 0;
    while (i < arr.size()) {
        if (flag == 1 || numb >= arr[i]) {
            arr_new[j++] = arr[i++];
        }
        else {
            arr_new[j++] = numb;
            flag = 1;
        }
    }
    output_vec(arr_new); 
    cout << endl;
    arr = arr_new;
}
int choice() {
    int task = 0;
    cout << "Выберете задание\n1 - Определить, упорядочены ли значения в массиве по возрастанию;\n";
    cout << "2 - Если значения в массиве не упорядочены по возрастанию, то удалить из массива элементы, которые кратны введенному значению;\n";
    cout << "3 - Если значения в массиве упорядочены по возрастанию, то вставить новый элемент в массив перед элементом с большим его по значению.\n";
    cin >> task;
    while (task != 1 && task != 2 && task != 3) {
        cout << "Неверный ввод. Повторите: ";
        cin >> task;
    }
    if (task == 1) {
        return 1;
    }
    if (task == 2) {
        return 2;
    }
    if (task == 3) {
        return 3;
    }
}
void stat() {
    int n = 0, ch;
    cout << "Введите количество обрабатываемых элементов массива(не больше 10): ";
    while (n <= 0 || n > Len) {
        cin >> n;
        cout << endl;
        if (n <= 0 || n > Len) {
            cout << "Введено неверное значение. Повторите ввод: ";
        }
    }
    int arr[Len];
    put(n, arr);
    output(arr, n);
    cout << endl;
    int a = 1;
    while (a != 0) {
        ch = choice();
        if (ch == 1) {
            if (order(arr, n) == 0) {
                cout << "Массив не упорядочен по возрастанию.\n";
            }
            else {
                cout << "Массив упорядочен по возрастанию.\n";
            }
        }
        else if (ch == 2) {
            if (order(arr, n) == 0) {
                task2_static(n, arr);
            }
            else {
                cout << "Массив упорядочен по возрастанию. Нельзя выполнить задание.\n";
            }
        }
        else {
            if (order(arr, n) == 0) {
                cout << "Массив не упорядочен по возрастанию. Нельзя выполнить задание.\n";
            }
            else {
                task3_static(n, arr);
            }

        }
        cout << "Если хотите начать работу с новым массивом, введите 0, для продолжения - 1.\n";
        cin >> a;
        while (a != 0 && a != 1) {
            cout << "Неверный ввод. Повторите.\n";
            cin >> a;
        }
    }
}
void dyn() {
    int n = 0, ch;
    cout << "Введите количество обрабатываемых элементов массива: ";
    cin >> n;
    while (n <= 0) {
        cin >> n;
        cout << endl;
        if (n <= 0) {
            cout << "Введено неверное значение. Повторите ввод: ";
        }
    }
    int* arr = new int[n];
    put(n, arr);
    output(arr, n);
    cout << endl;
    int a = 1;
    while (a != 0) {
        ch = choice();
        if (ch == 1) {
            if (order(arr, n) == 0) {
                cout << "Массив не упорядочен по возрастанию.\n";
            }
            else {
                cout << "Массив упорядочен по возрастанию.\n";
            }
        }
        else if (ch == 2) {
            if (order(arr, n) == 0) {
                task2_dyn(n, arr);
            }
            else {
                cout << "Массив упорядочен по возрастанию. Нельзя выполнить задание.\n";
            }
        }
        else {
            if (order(arr, n) == 0) {
                cout << "Массив не упорядочен по возрастанию. Нельзя выполнить задание.\n";
            }
            else {
                task3_dyn(n, arr);
            }

        }
        cout << "Если хотите начать работу с новым массивом, введите 0, для продолжения - 1.\n";
        cin >> a;
        while (a != 0 && a != 1) {
            cout << "Неверный ввод. Повторите.\n";
            cin >> a;
        }
    }
    delete[] arr;
}
void vec() {
    int n = 0, ch;
    cout << "Введите количество обрабатываемых элементов массива: ";
    cin >> n;
    while (n <= 0) {
        cin >> n;
        cout << endl;
        if (n <= 0) {
            cout << "Введено неверное значение. Повторите ввод: ";
        }
    }
    vector <int> arr(n);
    put_vec(arr);
    output_vec(arr);
    cout << endl;
    int a = 1;
    while (a != 0) {
        ch = choice();
        if (ch == 1) {
            if (order_vec(arr) == 0) {
                cout << "Массив не упорядочен по возрастанию.\n";
            }
            else {
                cout << "Массив упорядочен по возрастанию.\n";
            }
        }
        else if (ch == 2) {
            if (order_vec(arr) == 0) {
                task2_vec(arr);
            }
            else {
                cout << "Массив упорядочен по возрастанию. Нельзя выполнить задание.\n";
            }
        }
        else {
            if (order_vec(arr) == 0) {
                cout << "Массив не упорядочен по возрастанию. Нельзя выполнить задание.\n";
            }
            else {
                task3_vec(arr);
            }

        }
        cout << "Если хотите начать работу с новым массивом, введите 0, для продолжения - 1.\n";
        cin >> a;
        while (a != 0 && a != 1) {
            cout << "Неверный ввод. Повторите.\n";
            cin >> a;
        }
    }
}
int main() {
    setlocale(LC_ALL, "rus");
    int a = 1;
    while (a != 0) {
        int type = 0;
        cout << "Выберете массив: 0 - статический, 1 - динамический, 2 - вектор:\n";
        cin >> type;
        while (type != 0 && type != 1 && type != 2) {
            cout << "Неверный ввод. Повторите: ";
            cin >> type;
        }
        if (type == 0) {
            stat();
        }
        else if (type == 1) {
            dyn();
        }
        else {
            vec();
        }
        cout << "Если хотите завершить программу, введите 0, иначе - 1.\n";
        cin >> a;
        while (a != 0 && a != 1) {
            cout << "Неверный ввод. Повторите.\n";
            cin >> a;
        }
    }
    return 0;
}
