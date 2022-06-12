#ifndef __DYN_H__
#define __DYN_H__
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct subject
{
	int numb_group;
	int code_dis; //������ � ����������� (������) ���������
	short day;
	short numb_p;
	short numb_audit;
	short code_type; //������ � �����������(������) ���� ������� � �����
};

struct disdict //���������� ���������
{
	char name[25];//�������� ����������
};

struct distype //���������� ����� �������
{
	char type[25]; //�������� ����
	short hours; //����� �� �������
};

void input(subject& oneclass) { //1) ���������� ������ �� ������ ������� � ����������
	cout << "������� ����� ������: ";
	cin >> oneclass.numb_group;
	cout << "\n������� ��� ����������: ";
	cin >> oneclass.code_dis;
	cout << "\n������� ���� ������: ";
	cin >> oneclass.day;
	cout << "\n������� ����� ����: ";
	cin >> oneclass.numb_p;
	cout << "\n������� ����� ���������: ";
	cin >> oneclass.numb_audit;
	cout << "\n������� ��� ���� �������: ";
	cin >> oneclass.code_type;
}

void input_schedule(subject* schedule, int& N) { //2
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1; j++) {
			if (schedule[j].day > schedule[j + 1].day) {
				int b = schedule[j].day; 
				schedule[j].day = schedule[j + 1].day;
				schedule[j + 1].day = b;
			}
		}
	}	
}

void delete_(subject* schedule, int& N, int code) //3
{
	vector <int> index;
	for (int i = 0; i < N; i++) {
		if (schedule[i].code_dis == code) {
			index.push_back(i);
		}
	}
	int k = 0, i = 0;
	while (k < N) {
		if (find(index.begin(), index.end(), i) != index.end()) {
			if (k != N - 1) {
				subject temp = schedule[N - 1];
				schedule[N - 1] = schedule[k];
				for (int j = k; j < N - 2; j++) {
					schedule[j] = schedule[j + 1];
				}
				schedule[N - 2] = temp;
				N--;
				k--;
			}
			else {
				N--;
			}
			
		}
		k++;
		i++;
	}
}
void count_hours(subject* schedule, int& N, distype* disdictionary) {
	int h_t0 = 0, h_t1 = 0, h_t2 = 0, h_t3 = 0;
	for (int i = 0; i < N; i++) {
		if (schedule[i].code_type == 0) {
			h_t0 += 1;
		}
		else if (schedule[i].code_type == 1) {
			h_t1 += 1;
		}
		else if (schedule[i].code_type == 2) {
			h_t2 += 1;
		}
		else if (schedule[i].code_type == 3) {
			h_t3 += 1;
		}
	}
	cout << endl;
	cout << setw(30) << left << disdictionary[0].type << " - " << disdictionary[0].hours * h_t0 << " ����(��) � ������\n";
	cout << setw(30) << left << disdictionary[1].type << " - " << disdictionary[1].hours * h_t1 << " ����(��) � ������\n";
	cout << setw(30) << left << disdictionary[2].type << " - " << disdictionary[2].hours * h_t2 << " ����(��) � ������\n";
	cout << setw(30) << left << disdictionary[3].type << " - " << disdictionary[3].hours * h_t3 << " ����(��) � ������\n";
}
#endif