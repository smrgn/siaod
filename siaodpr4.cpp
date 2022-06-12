#include "dyn.h"
#include "vec.h"
#include <string>
#include <Windows.h>
using namespace std;

void create_disdictionary(distype* disdictionary) {
	strcpy_s(disdictionary[0].type, "лекция");
	disdictionary[0].hours = 2;
	strcpy_s(disdictionary[1].type, "практическое занятие");
	disdictionary[1].hours = 2;
	strcpy_s(disdictionary[2].type, "лабораторная работа");
	disdictionary[2].hours = 4;
	strcpy_s(disdictionary[3].type, "практика");
	disdictionary[3].hours = 2;
}
void create_disname(disdict* disname) {
	int v;
	cout << "Введите 1, если хотите заполнить справочник дисциплин самостоятельно, или 0, если хотите, чтобы справочник заполнился автоматически: ";
	cin >> v;
	while (v != 0 && v != 1) {
		cout << "Введено неверное число. Повторите ввод: ";
		cin >> v;
	}
	switch (v) {
	case 0:
		strcpy_s(disname[0].name, "Алгебра");
		strcpy_s(disname[1].name, "Программирование");
		strcpy_s(disname[2].name, "Мат. логика");
		strcpy_s(disname[3].name, "Иностранный язык");
		strcpy_s(disname[4].name, "Философия");
		break;
	case 1:
		cout << "Введите 5 дисциплин:\n";
		for (int i = 0; i < 5; i++) {
			cin >> disname[i].name;
		}
		break;
	}
}
void output_disdictionary(distype* disdictionary) {
	cout << endl;
	cout << "Справочник видов занятий и часов:\n";
	cout << setw(15) << left << "Код (индекс)" << setw(25) << left << "Вид занятия" << "Часы\n";
	for (int i = 0; i < 4; i++) {
		cout << setw(15) << left << i << setw(25) << left << disdictionary[i].type << disdictionary[i].hours << endl;
	}
}
void output_disname(disdict* disname) {
	cout << endl;
	cout << "Справочник дисциплин:\n";
	cout << setw(15) << left << "Код (индекс)" << "Название дисциплины\n";
	for (int i = 0; i < 5; i++) {
		cout << setw(15) << left << i << disname[i].name << endl;
	}
}
void test_case(subject& newclass, subject* schedule) {
	newclass.numb_group = 1;
	newclass.code_dis = 1;
	newclass.day = 3;
	newclass.numb_p = 1;
	newclass.numb_audit = 1;
	newclass.code_type = 1;
	schedule[0] = newclass;

	newclass.numb_group = 2;
	newclass.code_dis = 1;
	newclass.day = 2;
	newclass.numb_p = 3;
	newclass.numb_audit = 6;
	newclass.code_type = 0;
	schedule[1] = newclass;

	newclass.numb_group = 3;
	newclass.code_dis = 0;
	newclass.day = 4;
	newclass.numb_p = 1;
	newclass.numb_audit = 1;
	newclass.code_type = 3;
	schedule[2] = newclass;

	newclass.numb_group = 4;
	newclass.code_dis = 2;
	newclass.day = 3;
	newclass.numb_p = 1;
	newclass.numb_audit = 4;
	newclass.code_type = 0;
	schedule[3] = newclass;

	newclass.numb_group = 5;
	newclass.code_dis = 1;
	newclass.day = 1;
	newclass.numb_p = 1;
	newclass.numb_audit = 2;
	newclass.code_type = 1;
	schedule[4] = newclass;
}
void test_case_v(subject_v& newclass, vector <subject_v>& schedule) {
	newclass.numb_group = 1;
	newclass.code_dis = 1;
	newclass.day = 3;
	newclass.numb_p = 1;
	newclass.numb_audit = 1;
	newclass.code_type = 1;
	schedule.push_back(newclass);

	newclass.numb_group = 2;
	newclass.code_dis = 1;
	newclass.day = 2;
	newclass.numb_p = 3;
	newclass.numb_audit = 6;
	newclass.code_type = 0;
	schedule.push_back(newclass);

	newclass.numb_group = 3;
	newclass.code_dis = 0;
	newclass.day = 4;
	newclass.numb_p = 1;
	newclass.numb_audit = 1;
	newclass.code_type = 3;
	schedule.push_back(newclass);

	newclass.numb_group = 4;
	newclass.code_dis = 2;
	newclass.day = 3;
	newclass.numb_p = 1;
	newclass.numb_audit = 4;
	newclass.code_type = 0;
	schedule.push_back(newclass);

	newclass.numb_group = 5;
	newclass.code_dis = 1;
	newclass.day = 1;
	newclass.numb_p = 1;
	newclass.numb_audit = 2;
	newclass.code_type = 1;
	schedule.push_back(newclass);
}
void output_schedule(subject* schedule, int N, disdict* disname, distype* disdictionary) {
	cout << endl;
	cout << "Расписание:\n";
	cout << setw(12) << left << "№ группы" << setw(20) << left << "Дисциплина" << setw(15) << left << "День недели" << setw(15) << left << "Номер пары";
	cout << setw(20) << left << "Номер аудитории" << "Вид занятия\n";
	for (int i = 0; i < N; i++) {
		cout << setw(12) << left << schedule[i].numb_group << setw(18) << left << disname[schedule[i].code_dis].name << setw(15) << left << schedule[i].day << setw(15) << left << schedule[i].numb_p;
		cout << setw(20) << left << schedule[i].numb_audit << disdictionary[schedule[i].code_type].type << endl;
	}
}
void output_schedule_v(vector <subject_v>& schedule, int N, disdict* disname, distype* disdictionary) {
	cout << endl;
	cout << "Расписание:\n";
	cout << setw(12) << left << "№ группы" << setw(20) << left << "Дисциплина" << setw(15) << left << "День недели" << setw(15) << left << "Номер пары";
	cout << setw(20) << left << "Номер аудитории" << "Вид занятия\n";
	for (int i = 0; i < N; i++) {
		cout << setw(12) << left << schedule[i].numb_group << setw(18) << left << disname[schedule[i].code_dis].name << setw(15) << left << schedule[i].day << setw(15) << left << schedule[i].numb_p;
		cout << setw(20) << left << schedule[i].numb_audit << disdictionary[schedule[i].code_type].type << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	distype* disdictionary = new distype[4]; //справочник видов занятий
	create_disdictionary(disdictionary);

	disdict* disname = new disdict[5]; //справочник названий занятий
	create_disname(disname);

	output_disdictionary(disdictionary);
	output_disname(disname);

	int v;
	cout << "\nКак вы хотите выполнять работу:\n1 - с помощью динамического массива\n2 - с помощью вектора\n";
	cin >> v;
	while (v != 1 && v != 2) {
		cout << "Введено неверное число. Повторите ввод: ";
		cin >> v;
	}
	int test;
	cout << "Если хотите, чтобы все данные заполнились автоматически, введите 1, инчае - любое другое число: ";
	cin >> test;
	if (v == 1) {
		int N;
		subject* schedule = new subject[100]; //расписание
		subject newclass;

		if (test != 1) {
			cout << "\nВведите количество занятий: ";
			cin >> N;
			while (N <= 0) {
				cout << "Введено неверное число. Повторите ввод: ";
				cin >> N;
			}
			for (int i = 0; i < N; i++) {
				cout << "Заполните " << i + 1 << " запись: \n";
				input(newclass); //1 задание
				schedule[i] = newclass;
			}
		}
		else {
			N = 5;
			test_case(newclass, schedule);
		}
		input_schedule(schedule, N); //2 задание
		output_schedule(schedule, N, disname, disdictionary);
		int task3;
		int code;
		cout << "Если вы хотите удалить записи по какой-то дисциплине (выполнить 3 задание), введите 3, иначе - любое другое число: ";
		cin >> task3;
		while (task3 == 3) {
			cout << "Введите код дисциплины (записи по данной дисциплине будут удалены из расписания): ";
			cin >> code;
			delete_(schedule, N, code); //3 задание
			output_schedule(schedule, N, disname, disdictionary);
			cout << "Если хотите выполнить 3 задание еще раз, то введите 3, иначе - любое другое число: ";
			cin >> task3;
		}
		count_hours(schedule, N, disdictionary);
	}
	else {
		int N;
		vector <subject_v> schedule; //расписание
		subject_v newclass;
		if (test != 1) {
			cout << "\nВведите количество занятий: ";
			cin >> N;
			while (N <= 0) {
				cout << "Введено неверное число. Повторите ввод: ";
				cin >> N;
			}
			for (int i = 0; i < N; i++) {
				cout << "Заполните " << i + 1 << " запись: \n";
				input_v(newclass); //1 задание
				schedule.push_back(newclass);
			}
		}
		else {
			N = 5;
			test_case_v(newclass, schedule);
		}
		
		input_schedule_v(schedule, N); //2 задание
		output_schedule_v(schedule, N, disname, disdictionary);

		int task3;
		int code;
		cout << "Если вы хотите удалить записи по какой-то дисциплине (выполнить 3 задание), введите 3, иначе - любое другое число: ";
		cin >> task3;
		while (task3 == 3) {
			cout << "Введите код дисциплины (записи по данной дисциплине будут удалены из расписания): ";
			cin >> code;
			delete_v(schedule, N, code); //3 задание
			output_schedule_v(schedule, N, disname, disdictionary);
			cout << "Если хотите выполнить 3 задание еще раз, то введите 3, иначе - любое другое число: ";
			cin >> task3;
		}
		count_hours_v(schedule, N, disdictionary);
	}
	return 0;
}

