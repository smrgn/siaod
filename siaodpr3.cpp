#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <ctype.h>
#include <stdlib.h>
#include <fstream>
using namespace std;


int in_vec(vector<pair<char, int>> offsets, char c) {
	for (pair<char, int> p : offsets)
		if (p.first == c)
			return p.second;
	return 0;
}

vector<pair<char, int>> get_list_offsets(string pattern) { 
	vector<pair<char, int>> offsets;
	int size = pattern.size();
	for (int i = size - 2; i >= 0; i--) {
		if (!in_vec(offsets, pattern[i])) {
			offsets.push_back(pair<char, int>{pattern[i], size - i - 1}); //добавляем в массив смещений (элемент, смещение (число до последнего символа))
		}
	}
	if (!in_vec(offsets, pattern[size - 1]))
		offsets.push_back(pair<char, int>{pattern[size - 1], size});
	return offsets;
}

bool boyer_mur(string pattern, string s) { 
	vector<pair<char, int>> offsets = get_list_offsets(pattern);
	const int p_size = pattern.size();
	const int s_size = s.size();
	if (s_size < p_size)
		return false;
	int ind = p_size - 1;

	while (ind < s_size) {
		bool fl = true;
		for (int i = p_size - 1, j = ind; i >= 0; i--, j--) {
			if (s[j] != pattern[i]) {
				if (int d = in_vec(offsets, s[j])) {
					ind += d;
					cout << ' ' << d;
				}
				else {
					ind += p_size;
					cout << ' ' << p_size;
				}
				fl = false;
				break;
			}
		}
		if (fl)
			return true;
	}
	return false;
}

int task2() {
	string buf_line;
	string pattern; 
	ifstream file("test2.txt");
	if (!file.is_open())
		return 1;
	getline(file, pattern);
	while (getline(file, buf_line)) {
		cout << "............................." << endl << pattern << endl << buf_line << endl;
		cout << "offsets:";
		if (boyer_mur(pattern, buf_line))
			cout << endl << "YES" << endl;
		else
			cout << endl << "NO" << endl;
	}
	file.close();
}

int task1() {
	string text = "apple.application!juice:cat;camale?july."; // данный текст
	string subline; //подстрока, которую будем искать
	string word; 

	cout << "Введите подстроку:\n";
	getline(cin, subline); //считывание подстроки
	getline(cin, subline);

	vector <string> arr; //создание массива, куда будут записываться слова
	vector <string> arr_temp;

	for (int i = 0; i < text.size(); i++) {
		if (isalpha(text[i])) {
			word += text[i];
		}
		else {
			arr_temp.push_back(word);
			word = "";
		}
	}
	string cur_word;
	int flag;
	for (int i = 0; i < arr_temp.size(); i++) {
		flag = 1;
		cur_word = arr_temp[i];
		if (cur_word.size() >= subline.size()) {
			for (int j = 0; j < subline.size(); j++) {
				if (subline[j] != cur_word[j]) {
					flag = 0;
				}
			}
			if (flag) {
				arr.push_back(cur_word);
			}
		}
	}
	if (arr.size() == 0) {
		cout << "Таких слов не нашлось.";
		return 1;
	}
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int numb = 0;

	cout << "1) Дан текст, разделенных знаками препинания.\nСформировать";
	cout << "массив из слов, в которых заданная подстрока размещается с первой позиции.\n\n";
	cout << "2) В текстовом файле хранятся входные данные:\nна первой";
	cout << "сроке – подстрока(образец)длиной не более 17 символов для";
	cout << "поиска в тексте;\nсо второй строки – текст(строка), в котором";
	cout << "осуществляется поиск образца.\nСтрока, в которой надо искать, не";
	cout << "ограниченна по длине.\nПрименяя алгоритм Бойера - Мура с";
	cout << "турбосдвигом вывести индексы строки, на которые смещается";
	cout << "алгоритм при поиске вхождения образца.\n";
	cout << "\nВыберете задание, которое хотите выполнить:\n";
	cin >> numb;

	while (numb != 1 && numb != 2) {
		cout << "Неверный ввод. Повторите: ";
		cin >> numb;
	}
	switch (numb) {
	case 1: 
		task1();
		break;
	case 2:
		task2();
		break;
	}
	return 0;
}
