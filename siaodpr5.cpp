/*
Цель. Получение практических навыков по выполнению операций над
структурой данных граф
Задание. Выполнить разработку программы управления графом, в соответствии
с вариантом, на основе класса Граф. Предусмотреть в качестве данных:
количество вершин в графе, структура для хранения графа.*/


#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

struct Graph {
private:
	vector<vector<int>> connections;
public:
	void resizeConnections() {
		vector<int> vectConnections;
		this->connections.push_back(vectConnections);
		int size = connections.size();
		for (int i = 0; i < size; i++) {
			while (connections.at(i).size() != size)
				connections.at(i).push_back(0);
		}
	}
	void addNode() {
		this->resizeConnections();
	}
	void addConnection(int first, int second, int distance) {
		connections[first - 1][second - 1] = distance;
		connections[second - 1][first - 1] = 0;
	}
	int maxDistance() {
		int maxS = -10^99; 
		int size = connections.size();
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				if (connections[i][j] > maxS)
					maxS = connections[i][j];
		return maxS;
	}
	void graphTable() {
		cout << "\n\n";
		int size = connections.size();
		int tab = max(to_string(connections.size()).length(), to_string(this->maxDistance()).length());
		int digTab = to_string(connections.size()).length();
		cout << left << "\t#";
		for (int i = 0; i < digTab - 1; i++)
			cout << " ";
		cout << "| ";
		cout.flags(ios::left);
		for (int i = 0; i < size; i++) {
			cout << setw(tab + 1) << i + 1;
		}
		cout << endl;
		for (int i = 0; i < size; i++) {
			cout << "\t" << i + 1;
			for (int j = 0; j < digTab - 1; j++) {
				if (i < 9)
					cout << " ";
			}
			cout << "| ";
			for (int j = 0; j < size; j++) {
				cout << setw(tab + 1) << connections.at(i).at(j);
			}
			cout << "\n";
		}
	}

	int findShortestWay(int begin, int end) {
		cout << setw(connections.size()) << "\tTask: find shortest way between " << min(begin, end) << " and " << max(begin, end) << " nodes" << endl;
		begin--;
		end--;
		if (begin < 0)
			return 0;
		int minindex, minN, temp;
		int size = connections.size();
		int* d = new int[size];
		int* v = new int[size];
		for (int i = 0; i < size; i++) {
			d[i] = numeric_limits<int>::max();
			v[i] = 1;
		}
		d[begin] = 0;
		do {
			minindex = numeric_limits<int>::max();
			minN = numeric_limits<int>::max();
			for (int i = 0; i < size; ++i) {
				if (v[i] == 1 and d[i] < minN) {
					minN = d[i];
					minindex = i;
				}
			}
			if (minindex != numeric_limits<int>::max()) {
				for (int i = 0; i < size; ++i) {
					if (connections[minindex][i] > 0) {
						if (minN + connections[minindex][i] < d[i])
							d[i] = minN + connections[minindex][i];
					}
				}
				v[minindex] = 0;
			}
		} while (minindex < numeric_limits<int>::max());

		if (d[end] == numeric_limits<int>::max()) {
			cout << "\tThere's no way between " << min(begin + 1, end + 1) << " and " << max(begin + 1, end + 1) << " nodes" << endl;
			return 0;
		}

		cout << "\tShortest way length: " << d[end] << endl;

		int* ver = new int[size](); // массив посещенных вершин
		ver[0] = end + 1;
		int k = 1;
		int weight = d[end];

		while (end != begin) {
			for (int i = 0; i < size; i++)
				if (connections[i][end] != 0) {
					int temp = weight - connections[i][end]; // определяем вес пути
					if (temp == d[i]) {
						weight = temp; // сохраняем новый вес
						end = i;       // сохраняем предыдущую вершину
						ver[k] = i + 1;
						k++;
					}
				}
		}

		cout << "\tShortest way: ";

		for (int i = k - 1; i >= 0; i--) {
			cout << ver[i];
			if (i != 0)
				cout << "-";
		}
		return 0;
	}
};

void exampleGraph(Graph* gr) {
	for (int i = 0; i < 10; i++)
		gr->addNode();

	gr->addConnection(1, 2, 3);
	gr->addConnection(1, 3, 4);
	gr->addConnection(1, 4, 2);
	gr->addConnection(2, 6, 3);
	gr->addConnection(3, 6, 6);
	gr->addConnection(4, 5, 5);
	gr->addConnection(4, 6, 2);
	gr->addConnection(4, 6, 2);
	gr->addConnection(5, 7, 6);
	gr->addConnection(5, 9, 12);
	gr->addConnection(6, 5, 1);
	gr->addConnection(6, 7, 8);
	gr->addConnection(6, 8, 7);
	gr->addConnection(7, 10, 4);
	gr->addConnection(8, 10, 3);
	gr->addConnection(8, 10, 3);
	gr->addConnection(9, 10, 11);
	

	gr->graphTable();
	cout << "\n";
	gr->findShortestWay(1, 10);
}

void userGraph(Graph* gr) {
	cout << "Input size:\nSIZE = ";
	int size = 0;
	cin >> size;
	for (int i = 0; i < size; i++)
		gr->addNode();
	cout << "Input distance between nodes (0 if don't exist):\n";
	int distance = 0, start = 0, end = 0;
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			cout << i + 1 << "-" << j + 1 << ": ";
			cin >> distance;
			gr->addConnection(i + 1, j + 1, distance);
		}
	}
	cout << "START = ";
	cin >> start;
	cout << "END = ";
	cin >> end;
	gr->graphTable();
	gr->findShortestWay(start, end);
}

int main() {
	setlocale(LC_ALL, "Rus");
	Graph* graph = new Graph();
	int n = -1;

	while (n < 0 or n > 2) {
		cout << "Choose way to create your graph:\n"
			<< "1) Use graph from task example\n"
			<< "2) Input graph from keyboard\n"
			<< "Enter 0 to exit.\n";
		cin >> n;

		switch (n) {
		case 1:
			exampleGraph(graph);
			break;
		case 2:
			userGraph(graph);
			break;
		case 0:
			cout << "End of the program..." << endl;
			break;
		default:
			cout << "Error. Try again.\n";
			break;
		}
	}

	cout << "\n\n";

	return 0;
}