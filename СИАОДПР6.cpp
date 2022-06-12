// 1) Вычислить x1(x2+x3)(x4+x5+x6)....(x46+x47+...+x55). 2) Удаление двунаправленного списка
#include <ctime>
#include <iostream>
#define Size 55
using namespace std;
struct node {
    int number;
    node* prev;
    node* next;
};
void hand_input(int* arr) {
    for (int i = 0; i < Size; i++) {
        cin >> arr[i];
    }
}
void rand_input(int* arr) {
    srand(time(NULL));
    for (int i = 0; i < Size; i++) {
        arr[i] = rand() % 100;
    }
}
void output(int* arr) {
    for (int i = 0; i < Size; i++) {
        cout << arr[i] << " ";
    }
}
void count_iter(int* arr) {  
    int value = 0, a = 0;
    long long sum = 0;
    int counter = 1;
    long long answ = 1;
    while (value < Size) {
        while (a++ < counter) {
            sum += arr[value++];
        }
        answ *= sum;
        sum = 0;
        a = 0;
        counter += 1;       
    }
    cout << answ;
}
long long count_rec(int* arr, int value, int& counter)  {
    int a = 0;
    long long sum = 0;
    if (value < Size) {
        while (a++ < counter) {
            sum += arr[value++];
        }
        counter += 1;
    }
    if (value < Size) {
        sum *= count_rec(arr, value, counter);
    }
    return sum;

}
node* fill_list(node*& cur, int size, node* prev = NULL, int count = 1) {
    cur = new node;
    cin >> cur->number;
    cur->prev = prev;

    if (count == size)
        cur->next = NULL;
    else
        cur->next = fill_list(cur->next, size, cur, count + 1);

    return cur;
}
void output_list(node* root) {
    if (root == NULL) {
        return;
    }
    cout << " " << root->number;
    output_list(root->next);
    return;
}
void delit(node* root)
{
    node* temp;
    temp = root->next;
    if (temp != NULL) {
        temp->prev = NULL;
    }
    else {
        return;
    }
    free(root);   // освобождение памяти текущего корня
    delit(temp); // передача нового корня списка
}
void task2() {
    int size;
    cout << "Введите размер двунаправленного списка: ";
    cin >> size;
    node* list;
    cout << "Введите элементы двунаправленного списка: ";
    fill_list(list, size);
    cout << "\nДвунаправленный список (до удаления): ";
    output_list(list);
    int t0 = clock();
    delit(list);
    int t = clock();
    cout << "\nДвунаправленный список (после удаления): ";
    cout << "\nВремя выполнения алгоритма: " << t - t0 << endl;;
}
int main()
{
    setlocale(LC_ALL, "Rus");
    int type;
    cout << "Выберете задание:\n";
    cout << "1 - Вычислить x1(x2+x3)(x4+x5+x6)....(x46+x47+...+x55);\n";
    cout << "2 - удаление двунаправленного списка.\n";
    cin >> type;
    while (type != 1 && type != 2) {
        cout << "Неверный ввод. Повторите: ";
        cin >> type;
    }
    int value = 0, counter = 1;
    int t1, t2, t1start, t1end, t2start, t2end;
    switch (type) {
    case 1:
        int put;
        int arr[Size];
        cout << "Нажмите 1, если хотите заполнить массив руками, или 0, если хотите, чтобы массив заполнился случайными числами: ";
        cin >> put;
        while (put != 1 && put != 0) {
            cout << "Неверный ввод. Повторите: ";
            cin >> put;
        }
        if (put == 1) {
            hand_input(arr);
        }
        else {
            rand_input(arr);
            cout << "Массив: ";
            output(arr);
            cout << endl;
        }
        cout << "Вычесление итерационным способом: ";
        t1start = clock();
        count_iter(arr);
        t1end = clock();
        t1 = (t1end - t1start);
        cout << "\nВремя выполнения алгоритма: " << t1 << endl;;

        cout << "\nВычесление рекурсивным способом: ";
        t2start = clock();
        cout << count_rec(arr, value, counter);
        t2end = clock();
        t2 = (t2end - t2start);
        cout << "\nВремя выполнения алгоритма: " << t2 << endl;;
        break;
    case 2:
        task2();
        break;
    }
    return 0;
}


