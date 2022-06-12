#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;
void output_char(vector <char>& vec_itog) {
    cout << "Массив: ";
    for (int i = 0; i < vec_itog.size(); i++) {
        cout << vec_itog[i];
    }
    cout << endl;
}
void output(vector <string>& vector) {
    cout << "Массив: ";
    for (int i = 0; i < vector.size(); i++) {
        cout << vector[i] << " ";
    }
    cout << endl;
}
bool isend(string token, string substring) {
    if (token.length() < substring.length())return false;
    return token.substr(token.length() - substring.length(), token.length()) == substring;
}
int mind(string& delimiter, string s) {
    string delimiters[7] = { " ", ",",".","!",";",":","?"};
    int min = s.find(delimiters[0]);
    delimiter = " ";
    for (int i = 0; i < 7; i++) {
        if (s.find(delimiters[i]) < min) {
            min = s.find(delimiters[i]);
            delimiter = delimiters[i];
        }
    }
    return min;
}
void split_char(char* str, int& n, vector <char>& vec) {
    int j = 0;
    while (j != n) {
        if ((str[j] != ' ') && (str[j] != ',') && (str[j] != '.') && (str[j] != ';') && (str[j] != ':') && (str[j] != '!') && (str[j] != '?')) {
            vec.push_back(str[j]);
            j++;
        }
        else {
            vec.push_back(' ');
            j++;
        }
    }
}
void split(string s, vector<string>& vector, string substring) {
    size_t pos = 0;
    string token;
    string delimiter = "";
    while ((pos = mind(delimiter, s)) != string::npos) {
        token = s.substr(0, pos);
        if (token.find(substring) != -1 and token != " ") {
            vector.push_back(token);
        }
        s.erase(0, pos + delimiter.length());
    }
    if (token != " " and isend(s, substring)) {
        vector.push_back(s);
    }
}
void check(vector <char>& vec) {
    string subs;
    cout << "\nВведите подстроку: ";
    getline(cin, subs);
    vector <char> vec_itog = {};
    int begin = 0;
    for (int i = 0; i < vec.size(); i++) {
        int count = 0;
        if ((vec[i] == ' ') && (i + 1 != subs.size())) {
            int k = i - 1;
            for (int j = subs.size() - 1; j >= 0; j--) {
                if (vec[k--] == subs[j]) {
                    count += 1;
                }
            }
            if (count == subs.size()) {
                for (int x = begin; x < i; x++) {
                    vec_itog.push_back(vec[x]);
                }
                vec_itog.push_back(' ');
            }
            begin = i + 1;
        }
    }
    output_char(vec_itog);
}
void mas_char() {
    string text;
    int n;
    cout << "Введите длину вашей строки: ";
    cin >> n;
    cout << "Введите текст: ";
    getline(cin, text);
    getline(cin, text);
    char* str = new char[n];
    vector <char> vec = {};
    for (int i = 0; i < text.size(); i++) {
        str[i] = text[i];
    }
    cout << "Вы ввели: ";
    for (int i = 0; i < n; i++) {
        cout << str[i];
    }
    split_char(str, n, vec);
    check(vec);
    delete[] str;
}
void str() {
    string s, subs;
    vector <string> vector;
    cout << "Введите текст: ";
    getline(cin, s);
    getline(cin, s);
    cout << "\nВведите подстроку: ";
    cin >> subs;
    split(s, vector, subs);
    output(vector);
}
int main() {
    setlocale(LC_ALL, "rus");
    int type, a = 1;
    while (a != 0) {
        cout << "Задание: Дан текст, слова в котором разделены любыми допустимыми знаками препинания.\n";
        cout << "Сформировать массив из слов, в которых заданная подстрока размещается в конце слова.\n";
        cout << "Выберете каким способом решать: 1 - через массив char, 2 - через string: \n";
        cin >> type;
        while (type != 1 && type != 2) {
            cin >> type;
        }
        if (type == 1) {
            mas_char();
        }
        else {
            str();
        }
        cout << "Если хотите завершить программу, введите - 0, иначе любое другое число: ";
        cin >> a;
    }
}
