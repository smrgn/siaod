#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h> 
#include <vector>
#include <string>
#include <algorithm>
#include <chrono> 
#include <random>
#pragma warning(disable: 4996)
using namespace std;

struct branch
{
    char name[16];
    int code;
};

struct branch_vec
{
	int code;
	string name;
};

string create_name(vector<string> names)
{
	int n = names.size();
	return names[rand() % n];
}

int search_line(vector< branch_vec> table, int find_code)
{
	int flag = 0;
	for (int i = 0; i < table.size(); i++)
	{
		if (find_code == table[i].code)
		{
			cout << "Линейный поиск: " << table[i].code << " " << table[i].name << endl;
			flag = 1;
		}
	}
	if (!flag) {
		cout << "Специальность с таким кодом отсутствует. Повторите ввод: ";
	}
	return flag;
}

template<typename T>
int binary_search(const vector<T>& vec, T& item, int s1, int s2) {
	if (s1 > s2)
		return -1;

	auto middle = (s1 + s2) / 2;

	if (item == vec.at(middle))
		return middle;

	if (item > vec.at(middle))
		return binary_search(vec, item, middle + 1, s2);
	else
		return binary_search(vec, item, s1, middle - 1);
}

template<typename T>
int search_bin(const vector<T>& vec, T& item) {
	return binary_search(vec, item, 0, vec.size() - 1);
}

int BinSearch(vector<int> arr, int key)
{
	int l = 0; // нижняя граница
	int u = arr.size() - 1; // верхняя граница

	while (l <= u) {
		int m = (l + u) / 2;
		if (arr[m] == key) return m;
		if (arr[m] < key) l = m + 1;
		if (arr[m] > key) u = m - 1;
	}
	return -1;
}

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	vector<branch_vec> table; 
	vector<int> code_table; 
	vector<branch_vec> table_sorted; 
	branch_vec br_vec;
	vector <string> names = { "РТУ МИРЭА", "МГУ", "ВШЭ", "РАНХиГС", "МГТУ", "МПГУ", "ТвГУ", "НГУ", "СПбГУ", "ИТМО", "РГГУ" };

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine e(seed);

	int n, find_code;
	cout << "Введите количество специальностей: " << endl;
	cin >> n;

	cout << "Пожалуйста, ожидайте, идёт создание файла...\n";

	vector <int> n_vec;
	for (int i = 0; i < n; i++)
	{
		n_vec.push_back(i);
	}
	shuffle(n_vec.begin(), n_vec.end(), e);

	ofstream binFile("ninepr.bin", ios::binary);

	for (int i = 0; i < n; i++)
	{
		branch* br = new branch;
		br->code = 100001 + n_vec[i] * 17;
		if (i == n - 1)
		{
			br->code = 100000;
		}
		strcpy(br->name, create_name(names).c_str());
		binFile.write((char*)br, sizeof(branch));
	}
	binFile.close();
	branch* br = new branch;
	ifstream binFile2("ninepr.bin", ios::binary);
	while (binFile2.read((char*)br, sizeof(branch)))
	{
		br_vec.code = br->code;
		br_vec.name = br->name;
		table.push_back(br_vec);
		code_table.push_back(br->code);
	}
	sort(code_table.begin(), code_table.end());
	for (int i = 0; i < code_table.size(); i++)
	{
		for (int j = 0; j < table.size(); j++)
		{
			if (table[j].code == code_table[i])
			{
				br_vec.code = table[j].code;
				br_vec.name = table[j].name;

				table_sorted.push_back(br_vec);
			}
		}
	}
	cout << "Код специальности" << "   " << "Название вуза\n";
	for (int i = 0; i < table_sorted.size(); i++)
	{
		cout << table_sorted[i].code << "              " << table_sorted[i].name << endl;
	}

	cout << "\nВведите код специальности : ";
	cin >> find_code;
	clock_t start;
	double duration;
	start = clock();
	while (!search_line(table, find_code)) {
		cin >> find_code;
	}
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Линейный поиск " << n << " элементов: " << duration << "\n";

	start = clock();
	cout << "Бинарный поиск: ";
	int m = search_bin(code_table, find_code);
	cout << table_sorted[m].code << " " << table_sorted[m].name << endl;
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Бинарный поиск " << n << " элементов: " << duration << '\n';
}
