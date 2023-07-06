/*Задание
1. Разработайте приложение, которое использует хеш-таблицу для организации
прямого доступа к записям файла, структура записи которого приведена в
варианте.
Разработайте и реализуйте функции для операций:
    1) Хеш-функцию (метод определите сами).
    2) Прочитать запись из файла и вставки запись в таблицу (запись
включает: ключ и номер записи с этим ключом в файле).
    3) Удалить запись из таблицы и соответственно из файла.
    4) Найти запись с заданным ключом в файле, используя хеш-таблицу.
    5) Выполнить рехеширование.
2. Разработайте такие тесты, чтобы возникли коллизии.
3. Разработайте такие тесты, чтобы требовалось рехеширование.
4. Заполните файл большим количеством записей. Определите время чтения
записи с заданным ключом для первой записи файла, для последней и где-то
в середине. Убедитесь (или нет), что время доступа для всех записей
одинаково.
5. Выведите список индексов, которые формируются при вставке элементов в
таблицу.*/

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <iomanip>
#include <Windows.h>
using namespace std;

struct Student {
    int numb_rb; //номер зачетки (ключ)
    int numb_group;
    string name;
};

class HashMapTable
{
    int table_size; //размер хеш-таблицы
    list<int>* table; //указатель на массив, хранящий ключи
public:
    HashMapTable(int key) { //создание конструктора вышеуказанного класса, содержащего все методы
        this->table_size = key;
        table = new list<int>[table_size];
    }; 
    
    int hashFunction(int key) { // хэш-функция для вычисления индекса с использованием table_size и ключа
        return (key % table_size);
    }
    
    void insertElement(int key) { //вставка ключа в хеш таблицу
        int index = hashFunction(key);
        table[index].push_back(key);
    }; 
    
    void findElement(int key) {
        int index = hashFunction(key);
        list <int> ::iterator i; //поиск ключа по индексу
        for (i = table[index].begin(); i != table[index].end(); i++)
        {
            if (*i == key)
                break;
        }
        if (i != table[index].end())
            cout << "Хеш: " << index << endl;;
    }

    void deleteElement(int key) { //удаление ключа из хеш таблицы
        int index = hashFunction(key);

        list <int> ::iterator i; //поиск ключа по индексу
        for (i = table[index].begin(); i != table[index].end(); i++)
        {
            if (*i == key)
                break;
        }
        if (i != table[index].end()) //удаление ключа из хеш таблицы, если найден
            table[index].erase(i);
    }; 

    void displayHashTable() { //отображение полной хеш таблицы
        cout << "Хеш-таблица\n";
        cout << "Хеш:    Ключ:\n";
        for (int i = 0; i < table_size; i++) {
            cout << i;
            for (auto j : table[i]) // обход по последнему/текущему индексу
                cout << "   ==> " << j;
            cout << endl;
        }
    }; 
};

void output_student(Student* s, int n) { //вывод таблицы с данными студентов
    cout << endl;
    cout << "Студенты:\n";
    cout << setw(30) << left << "Номер зачетки(ключ)" << setw(30) << left << "Номер группы" << "Фамилия Имя\n";
    for (int i = 0; i < n; i++) {
        cout << setw(30) << left << s[i].numb_rb << setw(30) << left << s[i].numb_group << s[i].name << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int a;
    cout << "Хотите заполнить автоматически? 0 - да, 1 - нет, заполнить самостоятельно: ";
    cin >> a;
    while (a != 0 && a != 1) {
        cout << "Неверный ввод. Повторите: ";
        cin >> a;
    }
    int n;
    cout << "Введите количество студентов(для автоматического ввода необходимо ввести 5): ";
    cin >> n;
    while (n <= 0) {
        cout << "Неверный ввод. Повторите: ";
        cin >> n;
    }
    Student* s = new Student[n];
    int nz, ng;
    string name;
    switch (a) {
    case 0: {
        s[0] = { 1, 1, "Логвинов Максим" };
        s[1] = { 2, 1, "Савелко Дмитрий" };
        s[2] = { 3, 1, "Воловиков Влад" };
        s[3] = { 4, 2, "Соловьев Никита" };
        s[4] = { 5, 3, "Харитонова Настя" };
        break;
    }
    case 1: {
        for (int i = 0; i < n; i++) {
            cout << "Заполните информацию о " << i + 1 << " студенте:\n";
            cout << "Введите номер зачетки: ";
            cin >> nz;
            cout << "Введите номер группы: ";
            cin >> ng;
            cout << "Введите фамилию и имя: ";
            getline(cin, name);
            getline(cin, name);
            s[i] = { nz, ng, name };
        }

        break;
    }
    }
    output_student(s, n);

    cout << "Введите размер хеш-таблицы: ";
    int ts;
    cin >> ts;
    while (ts <= 0) {
        cout << "Неверный ввод. Повторите: ";
        cin >> ts;
    }
    HashMapTable ht(ts); // table_size хэш-таблицы как ts

    cout << "Заполнение хеш-таблицы элементами из таблицы 'Cтуденты'....\n";
    for (int i = 0; i < n; i++)
        ht.insertElement(s[i].numb_rb);

    ht.displayHashTable();
    int action = 0;
    while (action != 5) {
        cout << "Выберете, что хотите сделать:\n";
        cout << "1 - добавть новый элемент в хеш-таблицу;\n";
        cout << "2 - удалить элемент из хеш-таблицы;\n";
        cout << "3 - вывести хеш-таблицу;\n";
        cout << "4 - найти элемент по ключу;\n";
        cout << "5 - завершить выполнение программы.\n";
        cin >> action;
        switch (action) {
        case 1: {
            output_student(s, n); 
            int new_n;
            cout << "Сколько элементов вы хотите добавить?\n";
            cin >> new_n;
            while (new_n <= 0) {
                cout << "Неверный ввод. Повторите: ";
                cin >> new_n;
            }
            new_n += n;
            Student* new_arr = new Student[new_n];
            for (int i = 0; i < n; i++) {
                new_arr[i] = s[i];
            }
            for (int i = n; i < new_n; i++) {
                cout << "Введите номер зачетки: ";
                cin >> nz;
                cout << "Введите номер группы: ";
                cin >> ng;
                cout << "Введите фамилию и имя: ";
                getline(cin, name);
                getline(cin, name);
                new_arr[i] = { nz, ng, name };
            }
            for (int i = n; i < new_n; i++)
                ht.insertElement(new_arr[i].numb_rb);
            output_student(new_arr, new_n);
            ht.displayHashTable();
            break;
        }
        case 2: {
            cout << "Введите ключ(номер зачетки) студента: ";
            int key;
            cin >> key;
            ht.deleteElement(key); // удаление элемента из хеш-таблицы
            ht.displayHashTable();
            break;
        }
        case 3: {
            ht.displayHashTable(); // вывод окончательных данных хеш-таблицы
            break;
        }
        case 4: {
            cout << "Введите ключ(номер зачетки) студента: ";
            int key;
            cin >> key;
            ht.findElement(key);
            break;
        }
        case 5: {
            cout << "Работа программы завершена.";
            break;
        }
        }
    }
    return 0;
}