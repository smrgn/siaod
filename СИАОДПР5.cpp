#include <iostream>
#include <string>
#define double next->next
using namespace std;

struct letter {
    char c;
    letter* next;
};

struct word {
    letter* cur;
    word* next;
};

void make_list(letter* begin, string text) {
    for (int i = 0; i < text.length(); i++)
    {
        char ch = text[i];
        begin->c = ch;
        if (i < text.length() - 1) {
            begin->next = new letter;
            begin = begin->next;
        }
    }
    begin->next = NULL;
}

bool is_text(char c) {
    if ('A' <= c && c <= 'Z' || 'a' <= c && c <= 'z' || 'А' <= c && c <= 'Я' || 'а' <= c && c <= 'я')
        return true;
    else
        return false;
}

letter* find_first_text(letter* begin) {
    while (begin != NULL && !is_text(begin->c))
        begin = begin->next;
    return begin;
}

void add_words(word*& words, letter* n) { 
    words->next = new word;
    words = words->next;
    words->cur = n;
}

void convert_into_words(letter* begin, word*& words) { 
    letter* n = find_first_text(begin);
    word* words_pointer = words;
    words_pointer->cur = n;

    bool words_end = false;
    while (n != NULL) {
        if (n->next == NULL) {
            if (is_text(n->c)) {
                add_words(words_pointer, n);
                if (words_end) {
                    add_words(words_pointer, n);
                }
            }
            break;
        }

        if (is_text(n->c))
        {
            if (words_end) {
                add_words(words_pointer, n);
                words_end = false;
            }
        }

        if (!is_text(n->next->c))
        {
            if (!words_end) {
                add_words(words_pointer, n);
                words_end = true;
            }
        }
        n = n->next;
    }
    words_pointer->next = NULL;
}

void input_and_convert(letter*& begin, word*& words) { 
    string s;
    getline(cin, s);
    make_list(begin, s);
    convert_into_words(begin, words);
}

void output_list(letter*& begin) {
    letter* n = begin;
    while (n != NULL) {
        cout << n->c;
        n = n->next;
    }
    cout << "\n";
}

void delete_list(letter*& begin) { 
    while (begin) {
        letter* next = begin->next;
        delete begin;
        begin = next;
    }
}

void delete_list(word*& words) { 
    while (words) {
        word* next = words->next;
        delete words;
        words = next;
    }
}

void connect(word* words) { 
    words = words->next;
    while (words->next != NULL) {
        words->cur->next = new letter;
        words->cur->next->c = ' ';
        words->double->cur->next = NULL;
        words->cur->double = words->next->cur;
        words = words->next->next;
    }
    words->cur->next = NULL;
}

void put_last_word(word*& words) {
    word* n = words, * penult_word = new word;

    while (n->double != NULL)
    {
        if (n->double->double == NULL) {
            penult_word = n->next;
        }
        n = n->double;
    }
    penult_word->next = NULL;
    n->double = words;
    words = n;
}

void task1(letter*& begin, word*& words) {
    put_last_word(words);
    connect(words);
    begin = words->cur;
}

void delete_second_word(word*& words) {
    word* third = words->double->double;
    delete words->double->next;
    delete words->double;
    words->double = third;
}

void task2(letter*& begin, word*& words) {
    delete_second_word(words);
    connect(words);
    begin = words->cur;
}

void replace(word*& words, int l, word* new_word) {
    if (l == 1) {
        new_word->double = words->double;
        words = new_word;
        return;
    }
    word* n = words;
    l -= 2;
    while (l--) {
        n = n->double;
    }
    new_word->double = n->double->double;
    n->double = new_word;
}

void task3(letter*& begin, word*& words) {
    int l;
    cin >> l;
    cin.ignore();
    letter* new_letter_list = new letter;
    word* new_word_list = new word;
    input_and_convert(new_letter_list, new_word_list);
    replace(words, l, new_word_list);
    connect(words);
    begin = words->cur;
}

int main()
{
    system("chcp 1251");
    letter* begin = new letter;
    word* words = new word;
    cout << "Введите строку: \n";
    input_and_convert(begin, words);
    int type = 1;
    while (type != 0) {
        cout << "Выберете задание:\n1 - Разработать функцию, которая находит последнее слово и переставляет его в начало списка.\n";
        cout << "2 - Разработать функцию, которая удаляет второе слово.\n";
        cout << "3 - Разработать функцию, которая заменяет k - ое слово на новое слово.Длина нового слова может быть больше длины k - ого слова.\n";
        cin >> type;
        if (type == 1) {
            task1(begin, words);
            output_list(begin);
        }
        else if (type == 2) {
            task2(begin, words);
            output_list(begin);
        }
        else if (type == 3) {
            task3(begin, words);
            output_list(begin);
        }
        else {
            cout << "Неверно, повторите ввод: (для выхода введите 0)";
            cin >> type;
        }
    }

    delete_list(begin);
    delete_list(words);
}