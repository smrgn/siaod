#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
void mas_input(int* mas, int N)
{
	srand(time(0));
	for (int i = 0; i < N; i++) {
		mas[i] = rand();
	}
}
void mas_copy(int* mas_from, int* mas_copy, int N)
{
	for (int i = 0; i < N; i++) {
		mas_copy[i] = mas_from[i];
	}
}
void sort1(int* mas, int N, long long& c, long long& m) { // Функция пузырьковой сортировки
	for (int i = 0; i < N; i++) {
		c++;
		for (int j = 0; j < N - 1; j++) {
			c++;
			if (mas[j] > mas[j + 1]) {
				c++;
				int temp = mas[j]; // создали дополнительную переменную
				mas[j] = mas[j + 1]; // меняем местами
				mas[j + 1] = temp; // значения элементов
				m++;
			}
		}
	}
}
void sort2(int* mas, int count, long long &c, long long &m) // Функция Шейкер-сортировки
{
    int left = 0, right = count - 1; // левая и правая границы сортируемой области массива
    int flag = 1;  // флаг наличия перемещений
    // Выполнение цикла пока левая граница не сомкнётся с правой
    // и пока в массиве имеются перемещения
    while ((left < right) && flag > 0)
    {
		c++;
        flag = 0;
        for (int i = left; i < right; i++)  //двигаемся слева направо
        {
			c++;
            if (mas[i] > mas[i + 1]) // если следующий элемент меньше текущего,
            {                           // меняем их местами
				c++;               
                int t = mas[i];
                mas[i] = mas[i + 1];
                mas[i + 1] = t;
				m++;
                flag = 1;      // перемещения в этом цикле были
            }
        }
        right--; // сдвигаем правую границу на предыдущий элемент
        for (int i = right; i > left; i--)  //двигаемся справа налево
        {
			c++;
            if (mas[i - 1] > mas[i]) // если предыдущий элемент больше текущего,
            {    
				c++;                 // меняем их местами
                int t = mas[i];
                mas[i] = mas[i - 1];
                mas[i - 1] = t;
				m++;
                flag = 1;    // перемещения в этом цикле были
            }
        }
        left++; // сдвигаем левую границу на следующий элемент
    }
}
void sort3(int* mas, int N, int l, int r, long long& c, long long& m) { //сортировка простым слиянием
	if (r == l)
	{
		c++;
		return;
	}
	if (r - l == 1)
	{
		c++;
		if (mas[r] < mas[l])
		{
			c++;
			swap(mas[r], mas[l]);
			m++;
		}
		return;
	}
	int mid = (r + l) / 2;
	sort3(mas, N, l, mid, c, m);
	sort3(mas, N, mid + 1, r, c, m);
	int* buf = new int[N];
	int xl = l;
	int xr = mid + 1;
	int cur = 0;
	while (r - l + 1 != cur)
	{
		c++;
		if (xl > mid)
		{
			c++;
			buf[cur++] = mas[xr++];
			m++;
		}
		else if (xr > r)
		{
			c++;
			buf[cur++] = mas[xl++];
			m++;
		}
		else if (mas[xl] > mas[xr])
		{
			c++;
			buf[cur++] = mas[xr++];
			m++;
		}
		else
		{
			buf[cur++] = mas[xl++];
			m++;
		}
	}
	for (int i = 0; i < cur; i++)
	{
		c++;
		mas[i + l] = buf[i];
		m++;
	}
	delete[] buf;
}
int main()
{
	setlocale(LC_CTYPE, "Russian");
	int start = 0;
	while (start != 1) {
		cout << "Для запуска программы введите - 1: ";
		cin >> start;
	}
	for (int i = 20000; i <= 80000; i += 15000) {
		cout << "количество элементов: " << i << endl;
		long long c1, c2, c3, m1, m2, m3;
		c1 = c2 = c3 = m1 = m2 = m3 = 0;
		int* mas1 = new int[i];
		int* mas2 = new int[i];
		int* mas3 = new int[i];
		mas_input(mas1, i);
		mas_copy(mas1, mas2, i);
		mas_copy(mas1, mas3, i);

		long double time1start = clock();
		sort1(mas1, i, c1, m1);
		long double time1end = clock();

		long double time1 = (time1end - time1start) / CLOCKS_PER_SEC;

		long double time2start = clock();
		sort2(mas2, i, c2, m2);
		long double time2end = clock();

		long double time2 = (time2end - time2start) / CLOCKS_PER_SEC;

		long double time3start = clock();
		sort3(mas3, i, 0, i - 1, c3, m3);
		long double time3end = clock();

		long double time3 = (time3end - time3start) / CLOCKS_PER_SEC;

		cout << "Средний случай:\n";
		cout << "Для пузырьковой сортировки: " << "время работы в секундах: " << time1 << " | С + M: " << c1 + m1 << endl;
		cout << "Для Шейкер-сортировки: " << "время работы в секундах: " << time2 << " | С + M: " << c2 + m2 << endl;
		cout << "Для сортировки слиянием: " << "время работы в секундах: " << time3 << " | С + M: " << c3 + m3 << endl;
		c1 = c2 = c3 = m1 = m2 = m3 = 0;

		time1start = clock();
		sort1(mas1, i, c1, m1);
		time1end = clock();

		time1 = (time1end - time1start) / CLOCKS_PER_SEC;

		time2start = clock();
		sort2(mas2, i, c2, m2);
		time2end = clock();

		time2 = (time2end - time2start) / CLOCKS_PER_SEC;

		time3start = clock();
		sort3(mas3, i, 0, i - 1, c3, m3);
		time3end = clock();

		time3 = (time3end - time3start) / CLOCKS_PER_SEC;

		cout << "Лучший случай:\n";
		cout << "Для пузырьковой сортировки: " << "время работы в секундах: " << time1 << " | С + M: " << c1 + m1 << endl;
		cout << "Для Шейкер-сортировки: " << "время работы в секундах: " << time2 << " | С + M: " << c2 + m2 << endl;
		cout << "Для сортировки слиянием: " << "время работы в секундах: " << time3 << " | С + M: " << c3 + m3 << endl;
		c1 = c2 = c3 = m1 = m2 = m3 = 0;

		sort(mas1, mas1 + i, greater<int>()); //делаем худший случай
		sort(mas2, mas2 + i, greater<int>());
		sort(mas3, mas3 + i, greater<int>());

		time1start = clock();
		sort1(mas1, i, c1, m1);
		time1end = clock();

		time1 = (time1end - time1start) / CLOCKS_PER_SEC;

		time2start = clock();
		sort2(mas2, i, c2, m2);
		time2end = clock();

		time2 = (time2end - time2start) / CLOCKS_PER_SEC;

		time3start = clock();
		sort3(mas3, i, 0, i - 1, c3, m3);
		time3end = clock();

		time3 = (time3end - time3start) / CLOCKS_PER_SEC;

		cout << "Худший случай:\n";
		cout << "Для пузырьковой сортировки: " << "время работы в секундах: " << time1 << " | С + M: " << c1 + m1 << endl;
		cout << "Для Шейкер-сортировки: " << "время работы в секундах: " << time2 << " | С + M: " << c2 + m2 << endl;
		cout << "Для сортировки слиянием: " << "время работы в секундах: " << time3 << " | С + M: " << c3 + m3 << endl;
		cout << endl;
	}
	return 0;
}