#include <iostream>
#include <new>
using namespace std;

// Структура, описывающая узел
template <typename T>
struct KnotStack
{
    T item;
    KnotStack<T>* next;
};

// Шаблонный класс Стек на базе односвязного списка
template <typename T>
class Stack_knot
{
private:
    KnotStack<T>* pHead; // указатель на вершину стека

public:
    // конструктор по умолчанию
    Stack_knot() { pHead = nullptr; }

    // конструктор копирования
    Stack_knot(const Stack_knot& stack)
    {
        KnotStack<T>* p; // дополнительные указатели
        KnotStack<T>* p2;
        KnotStack<T>* p3;

        // Инициализировать pTop
        pHead = nullptr;
        p3 = nullptr;

        p = stack.pHead; // указатель p движется по списку SL.pHead->...
        while (p != nullptr)
        {
            // 1. Сформировать узел p2
            try {
                // попытка выделения памяти
                p2 = new KnotStack<T>;
            }
            catch (bad_alloc e)
            {
                // если память не выделена, то выход
                cout << e.what() << endl;
                return;
            }
            p2->item = p->item;
            p2->next = nullptr;

            // 2. pHead = pHead + p2
            if (pHead == nullptr) // создать очередь
            {
                pHead = p2;
                p3 = p2;
            }
            else
            {
                p3->next = p2;
                p3 = p3->next;
            }

            // 3. Перейти на следующий элемент
            p = p->next;
        }
    }

    // поместить элемент в стек
    // элемент помещается на начало списка
    void push_knot(T item)
    {
        KnotStack<T>* p;

        // 1. Сформировать элемент
        try {
            p = new KnotStack<T>; // попытка выделить память
        }
        catch (bad_alloc e)
        {
            // если память не выделилась, то выход
            cout << e.what() << endl;
            return;
        }
        p->item = item;
        p->next = pHead; // p указывает на 1-й элемент

        // 2. Перенаправить pTop на p
        pHead = p;
    }

    // Количество элементов в стеке
    int count_knot()
    {
        if (pHead == nullptr)
            return 0;
        else
        {
            KnotStack<T>* p = pHead;
            int count = 0;

            while (p != nullptr)
            {
                count++;
                p = p->next;
            }
            return count;
        }
    }
    bool isEmpty_knot()
    {
        if (pHead == nullptr)
            return true;
        else
        {
            return false;
        }

    }
    // очищает стек - удаляет все элементы из стека
    void empty_knot()
    {
        KnotStack<T>* p; // дополнительный указатель
        KnotStack<T>* p2;

        p = pHead;

        while (p != nullptr)
        {
            p2 = p; // сделать копию из p
            p = p->next; // перейти на следующий элемент стека
            delete p2; // удалить память, выделенную для предыдущего элемента
        }
        pHead = nullptr; // поправить вершину стека
    }

    // вывод стека
    void print_knot()
    {
        cout << "Stack: " << endl; 
        if (pHead == nullptr)
            cout << "stack is empty." << endl;
        else
        {
            KnotStack<T>* p; // дополнительный указатель
            p = pHead;
            while (p != nullptr)
            {
                cout << p->item << " ";
                p = p->next;
            }
            cout << endl;
        }
    }

    // деструктор
    ~Stack_knot()
    {
        empty_knot();
    }

    // метод, вытягивающий элемент со стека
    T pop_knot()
    {
        // проверка, пуст ли стек?
        if (pHead == nullptr)
            return 0;

        KnotStack<T>* p2; // дополнительный указатель
        T item;
        item = pHead->item;

        // перенаправить указатели pTop, p2
        p2 = pHead;
        pHead = pHead->next;

        // Освободить память, выделенную под 1-й элемент
        delete p2;

        // вернуть item
        return item;
    }
};
// класс, реализующий стек в виде динамического массива
template <typename T>
class Stack_arr
{
private:
    T* stack; // Динамический масив-указатель на стек
    unsigned int count; // Вершина стека - количество элементов типа T в стеке

public:
    // конструктор по умолчанию
    Stack_arr()
    {
        stack = nullptr; // необязательно
        count = 0; // количество элементов в стеке определяется по значению count
    }

    // поместить элемент в стек
    void push_arr(T item)
    {
        T* tmp; // временный указатель

        // блок try необходим для перехвата исключения, если память не выделится
        try {
            // указатель указывает на stack
            tmp = stack;

            // выделить память на 1 элемент больше, чем было выделено до этого
            stack = new T[count + 1];

            // увеличить количество элементов в стеке на 1
            count++;

            // скопировать данные из памяти, на которую указывает tmp в память,
            // на которую указывает stack
            for (int i = 0; i < count - 1; i++)
                stack[i] = tmp[i];

            // добавить последний элемент
            stack[count - 1] = item;

            // освободить память, выделенную перед этим для stack,
            // на эту память указывает tmp
            if (count > 1)
                delete[] tmp;
        }
        catch (bad_alloc e)
        {
            // если память не выделилась
            cout << e.what() << endl;
        }
    }

    // Вытягнуть элемент из стека
    // При вытягивании элемента из стека память не переопределяется
    T pop_arr()
    {
        if (count == 0)
            return 0; // стек пуст
        count--;
        return stack[count];
    }

    // конструктор копирования STACK(const STACK&) - необходим для избежания
    // недостатков побитового копирования
    Stack_arr(const Stack_arr& st)
    {
        try {
            // 1. Выделить новый участок памяти для массива stack
            stack = new T[st.count];

            // 2. Скопировать данные из st в текущий объект
            count = st.count;
            for (int i = 0; i < count; i++)
                stack[i] = st.stack[i];
        }
        catch (bad_alloc e)
        {
            // если память не выделилась, то вывести соответствующее сообщение
            cout << e.what() << endl;
        }
    }

    // операторная функция operator=(const STACK&) - необходима для избежания
    // недостатков побитового копирования
    Stack_arr operator=(const Stack_arr& st)
    {
        // Нужно скопировать из st в текущий объект
        // 1. Освободить предварительно выделенную память для текущего объекта
        if (count > 0)
        {
            count = 0;
            delete[] stack; // освободить память под предыдущий массив
        }

        // 2. Выделить новый участок памяти для массива stack
        try {
            // попытка выделить память
            stack = new T[st.count];

            // 3. Скопировать данные из st в текущий объект
            count = st.count;
            for (int i = 0; i < count; i++)
                stack[i] = st.stack[i];
        }
        catch (bad_alloc e)
        {
            // если не удалось виделить память, то вывести соответствующее сообщение
            cout << e.what() << endl;
        }

        // 4. Вернуть текущий объект
        return *this;
    }

    // Деструктор - освобождает память
    ~Stack_arr()
    {
        if (count > 0)
            delete[] stack;
    }

    // Количество элементов в стеке
    int count_arr()
    {
        return count;
    }

    // Функция, которая определяет пуст ли стек
    bool isEmpty_arr()
    {
        return count == 0;
    }

    // Функция, выводящая стек
    void print_arr()
    {
        T* p; // временный указатель, двигается по элементах стека

        // 1. Установить указатель p на вершину стека
        p = stack;

        // 2. Вывод
        cout << "Stack: " << endl;
        if (count == 0)
            cout << "is empty." << endl;

        for (int i = 0; i < count; i++)
        {
            cout << "Item[" << i << "] = " << *p << endl;
            p++; // прокрутить указатель на следующий элемент
        }
        cout << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    Stack_knot<int> stack1;
    Stack_knot<int> stack2;
    Stack_knot<int> stacktotal;

    string numb1, numb2;
    int md, value, el1, el2, el;
    md = 0;

    cout << "Введите 2 числа: " << endl;
    cin >> numb1;
    cin >> numb2;

    for (int i = 0; i < numb1.size(); i++)
    {
        stack1.push_knot(numb1[i] - '0');
    }
    for (int i = 0; i < numb2.size(); i++)
    {
        stack2.push_knot(numb2[i] - '0');
    }

    while (!(stack1.isEmpty_knot()) and !(stack2.isEmpty_knot()))
    {
        el1 = stack1.pop_knot();
        el2 = stack2.pop_knot();
        value = (el1 + el2 + md) % 10;
        stacktotal.push_knot(value);
        md = (el1 + el2) / 10;
    }

    if (stack1.count_knot() == stack2.count_knot())
    {
        stacktotal.push_knot(md);
    }
    else if ((stack1.count_knot() > stack2.count_knot()) and !(stack1.isEmpty_knot()))
    {
        while (!(stack1.isEmpty_knot()))
        {
            el = stack1.pop_knot();
            stacktotal.push_knot(el + md);
        }
    }
    else if ((stack2.count_knot() > stack1.count_knot()) and !(stack2.isEmpty_knot()))
    {
        while (!(stack2.isEmpty_knot()))
        {
            el = stack2.pop_knot();
            stacktotal.push_knot(el + md);
        }
    }
    stacktotal.print_knot();
    return 0;
}