#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
const int rows = 10;
const int cols = 10;
using namespace std;
void put_r_stat(int mat[::rows][::cols], int& n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = rand() % 10;
        }
    }
}
void put_stat(int mat[::rows][::cols], int &n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "mat[" << i << "][" << j << "] = ";
            cin >> mat[i][j];
        }
    }
}
void put_r_dyn(int** mat, int &n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = rand() % 10;
        }
    }
}
void put_dyn(int** mat, int& n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "mat[" << i << "][" << j << "] = ";
            cin >> mat[i][j];
        }
    }
}
void put_vec(vector <vector <int>> &matA, int &n) {
    matA.resize(n);
    for (int i = 0; i < n; i++) {
        matA[i].resize(n);
        for (int j = 0; j < n; j++) {
            cout << "matA[" << i << "][" << j << "] = ";
            cin >> matA[i][j];
        }
    }
    cout << endl;
}
void put(vector <int> &matB, int&n) {
    matB.resize(n);
    for (int i = 0; i < n; i++) {
        cout << "matB[" << i << "] = ";
        cin >> matB[i];
    }
}
void output_stat(int mat[::rows][::cols], int& n) {
    cout << "Матрица: \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}
void output_dyn(int** mat, int& n) {
    cout << "Матрица: \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}
void output_vec(vector <vector <int>>& matA, vector <int> &matB, int& n) {
    cout << "Система:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j != n - 1) {
                cout << matA[i][j] << "*x" << j << " + ";
            }
            else {
                cout << matA[i][j] << "*x" << j << " = ";
            }
        }
        cout << matB[i] << endl;
    }
}
void task1(int mat[::rows][::cols], int &n) {
    int r, min_r = 1;
    int new_mat[::rows][::cols];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            new_mat[i][j] = mat[i][j];
            int count = 0, flag = 1;
            if (mat[i][j] == 0) {
                int arr[4] = { 0, 0, 0, 0 }, x = 0;
                for (int p = 0; p < n; p++) {
                    for (int q = 0; q < n; q++) {
                        r = abs(i - p) + abs(j - q);
                        if (r == min_r) {
                            arr[x++] = mat[p][q];
                        }
                    }
                }
                for (int x = 0; x < 4; x++) {
                    if (arr[x] != 0) {
                        count += 1;
                        if (count > 1) {
                            flag = 0;
                        }
                    }
                }
                if (flag == 1) {
                    for (int x = 0; x < 4; x++) {
                        if (arr[x] != 0) {
                            new_mat[i][j] = arr[x];
                        }
                    }
                }
            }
        }
    }
    output_stat(new_mat, n);
}
void task2(int** mat, int &n) {
    int r, min_r = 1;
    int** new_mat = new int* [n];
    for (int i = 0; i < n; i++) {
        new_mat[i] = new int[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            new_mat[i][j] = mat[i][j];
            int count = 0, flag = 1;
            if (mat[i][j] == 0) {
                int arr[4] = { 0, 0, 0, 0 }, x = 0;
                for (int p = 0; p < n; p++) {
                    for (int q = 0; q < n; q++) {
                        r = abs(i - p) + abs(j - q);
                        if (r == min_r) {
                            arr[x++] = mat[p][q];
                        }
                    }
                }
                for (int x = 0; x < 4; x++) {
                    if (arr[x] != 0) {
                        count += 1;
                        if (count > 1) {
                            flag = 0;
                        }
                    }
                }
                if (flag == 1) {
                    for (int x = 0; x < 4; x++) {
                        if (arr[x] != 0) {
                            new_mat[i][j] = arr[x];
                        }

                    }
                }
            }
        }
    }
    output_dyn(new_mat, n);
    delete[] new_mat;
}
void task3(vector <vector <int>>& matA, vector <int>& matB, int& n) {
    vector <float> x(n);
    int j = n, s = n - 1;
    for (int d = 0; d < n; d++) {
        x[d] = 0;
    }
    for (int i = n - 1; i >= 0; i--) {
        float element = 0;
        for (int j_ = 0; j_ < n; j_++) {
            element += (x[j_] * matA[s][j_]);
        }
        s--;
        x[i] = ((matB[i] - element) / matA[i][--j]);
    }
    cout << "Решение:\n";
    for (int a = 0; a < n; a++) {
        cout << "x" << a << " = " << x[a] << endl;
    }
}
void stat() {
    int mat[::rows][::cols];
    int var = 0, n;
    cout << "Введите одним числом количесвто строк и столбцов в матрице(не бoльше 10): ";
    cin >> n;
    while (n <= 0 || n > ::rows) {
        cout << "Введено неверное значение. Повторите ввод: ";
        cin >> n;
    }
    cout << "Хотите заполнить матрицу самостоятельно, введите 0, или случайными числами - 1.\n";
    cin >> var;
    while (var != 0 && var != 1) {
        cout << "Введено неверное значение. Повторите ввод: ";
        cin >> var;
    }
    if (var == 0) {
        put_stat(mat, n);
    }
    else {
        put_r_stat(mat, n);
    }
    output_stat(mat, n);
    task1(mat, n);
}
void dyn() {
    int var = 0, n;
    cout << "Введите одним числом количесвто строк и столбцов в матрицe: ";
    cin >> n;
    while (n <= 0) {
        cout << "Введено неверное значение. Повторите ввод: ";
        cin >> n;
    }
    int** mat = new int* [n];
    for (int i = 0; i < n; i++) {
        mat[i] = new int[n];
    }
    cout << "Хотите заполнить матрицу самостоятельно, введите 0, или случайными числами - 1.\n";
    cin >> var;
    while (var != 0 && var != 1) {
        cout << "Введено неверное значение. Повторите ввод: ";
        cin >> var;
    }
    if (var == 0) {
        put_dyn(mat, n);
    }
    else {
        put_r_dyn(mat, n);
    }
    output_dyn(mat, n);
    task2(mat, n);
    delete[] mat;
}
void vec() {
    int n = 0;
    vector <vector <int>> matA;
    vector <int> matB(n);
    cout << "Введите количество уравнений: ";
    cin >> n;
    while (n <= 0) {
        cout << "Введено неверное значение. Повторите ввод: ";
        cin >> n;
    }
    put_vec(matA, n);
    put(matB, n);
    output_vec(matA, matB, n);
    task3(matA, matB, n);
}
int main()
{
    setlocale(LC_ALL, "rus");
    int a = 1;
    while (a != 0) {
        int type = 0;
        cout << "Выберете задание: \n";
        cout << "1) Дана матрица a размером n*n, заполненная неотрицательными целыми числами.";
        cout << "Расстояние между двумя элементами aij и apq определено как |i-p| + |j-q|.\n";
        cout << "Требуется заменить каждый нулевой элемент матрицы ближайшим ненулевым. Если есть две или больше ближайших ненулевых ячейки, нуль должен быть оставлен.\n";
        cout << "2) Дана система линейных алгебраических уравнений АХ=В. Найти решение системы из n линейных уравнений, рассматривая ее как треугольную.\n";
        cout << "Введите:\n- 1, чтобы решить 1 задачу через статический массив,\n- 2, чтобы решить 1 задачу через статический массив,\n- 3, чтобы решить 2 задачу.\n";
        cin >> type;
        while (type != 1 && type != 2 && type != 3) {
            cout << "Неверный ввод. Повторите: ";
            cin >> type;
        }
        if (type == 1) {
            stat();
        }
        else if (type == 2) {
            dyn();
        }
        else {
            vec();
        }
        cout << "Если хотите завершить программу, введите 0, иначе - 1.\n";
        cin >> a;
        while (a != 0 && a != 1) {
            cout << "Неверный ввод. Повторите.\n";
            cin >> a;
        }
    }
    return 0;
}
