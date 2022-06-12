#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include<regex>
#include <Windows.h>
#include <unordered_map>
using namespace std;

vector<int> prefix_func(const string& s) {
    vector<int> p(s.length());

    int k = 0;
    p[0] = 0;
    for (int i = 1; i < s.length(); ++i) {
        while (k > 0 && s[k] != s[i]) {
            k = p[k - 1];
        }
        if (s[k] == s[i]) {
            ++k;
        }
        p[i] = k;
    }
    return p;
}

int find(string& s, string& t, unsigned long long &c) {
    c++;
    if (s.length() < t.length()) {
        return -1;
    }
    c++;
    if (!t.length()) {
        return s.length();
    }

    typedef unordered_map<char, int> TStopTable;
    typedef unordered_map<int, int> TSufficsTable;
    TStopTable stop_table;
    TSufficsTable suffics_table;

    c++;
    for (int i = 0; i < t.length(); ++i) {
        c++;
        stop_table[t[i]] = i;
    }

    string rt(t.rbegin(), t.rend());
    vector<int> p = prefix_func(t), pr = prefix_func(rt);
    c++;
    for (int i = 0; i < t.length() + 1; ++i) {
        c++;
        suffics_table[i] = t.length() - p.back();
    }

    c++;
    for (int i = 1; i < t.length(); ++i) {
        c++;
        int j = pr[i];
        suffics_table[j] = min(suffics_table[j], i - pr[i] + 1);
    }

    c++;
    for (int shift = 0; shift <= s.length() - t.length();) {
        c++;
        int pos = t.length() - 1;

        while (t[pos] == s[pos + shift]) {
            c++;
            if (pos == 0)
            {
                c++;
                return shift;
            }
            --pos;
        }

        if (pos == t.length() - 1) {
            c++;
            TStopTable::const_iterator stop_symbol = stop_table.find(s[pos + shift]);
            int stop_symbol_additional = pos - (stop_symbol != stop_table.end() ? stop_symbol->second : -1);
            shift += stop_symbol_additional;
        }
        else {
            c++;
            shift += suffics_table[t.length() - pos - 1];
        }
    }

    return -1;
}



int quantity_of_substrings(string str, string& substr, unsigned long long &c)
{
    int pos = 0;
    int q = 0;
    while (pos != -1)
    {
        pos = find(str, substr, c);
        if (pos != -1)
        {
            q++;
            str.erase(0, pos + substr.length());
        }
    }
    return q;
}

string generate_random_text(int n)
{
    vector<string> words = { "головная боль 09.03.21", "зубная боль 03.10.21", "сдача анализов 19.02.19", "зубная боль 24.10.21", "сдача анализов 28.04.19", " узи 10.10.21" };
    vector<string> names = { "СВВааааааа", "ВАВооооооо", "СДАууууууу", "ОВАппппппп", "ММПггггггг" };
    int w, r;
    string text = "";
    srand(time(0));
    for (int i = 0; i < n/25; i++)
    {
        r = rand() % words.size();
        w = rand() % names.size();
        text += names[w] + " " + words[r] + " ";
    }
    return text;
}


int main() {
	setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int exs;
    string numb, info, s;
    unsigned long long c = 0;
    smatch m;
    regex e("([0-9a-z_]+)([\-*\/\+])");
    cout << "Выберете задание:\n1 - найти, сколько раз пациент обращался в клинику;\n2 - Регулярные выражения.\n";
    cin >> exs;
    switch (exs) {
    case 1:
        cout << "Все пациенты: СВВааааааа, ВАВооооооо, СДАууууууу, ОВАппппппп, ММПггггггг.\n";
        cout << "Введите номер карты пациента: ";
        getline(cin, numb);
        getline(cin, numb);
        for (int n = 100000; n <= 500000; n += 100000) {
            cout << "\nn = " << n << " " << "Количество раз = ";
            info = generate_random_text(n);
            cout << quantity_of_substrings(info, numb, c);
            cout << "\nC + M = " << c << endl;
            c = 0;
        }
        break;

    case 2:
        cout << "Введети алгебраическое выражение: ";

        getline(cin, s);
        getline(cin, s);

        cout << regex_replace(s, e, "0$2");
        
        break;
    }
	return 0;
}
