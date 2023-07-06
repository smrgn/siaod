/*Тема. Кодирование и сжатие данных методами без потерь.
Цель. Получение практических навыков и знаний по выполнению сжатия
данных рассматриваемыми методами

Разработать программы (или только алгоритмы на
псевлокоде или словесно) сжатия и восстановления текста
методами Шеннона-Фано и Хаффмана.
Провести кодирование(сжатие) исходной строки символов «Фамилия Имя
Отчество» с использованием алгоритма Хаффмана.*/

#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

//Шеннон-Фано
struct node {
    char sym;
    int frq;
    string code;
    node* left;
    node* right;
    node(char sym, int frq) {
        this->sym = sym;
        this->frq = frq;
        code = "";
        left = nullptr;
        right = nullptr;
    }
    node() {
        node(0, 0);
    }
};

// Шенонн-Фано от левого до правого включительно
node* shennon_fano(int l, int r, vector<node> array) {
    // лист готов
    if (l == r) return new node(array[l].sym, array[l].frq);

    // поиск точки разбиения - middle
    int left_sum = 0, right_sum = 0;
    for (int i = l; i <= r; i++) right_sum += array[i].frq;
    int middle; // последний элемент левого множества
    for (middle = l; middle < r; middle++) {
        left_sum += array[middle].frq;
        right_sum -= array[middle].frq;
        if (left_sum > right_sum) break;
    }
    if (middle == r) middle--;
    if (abs((left_sum - array[middle].frq) - (right_sum + array[middle].frq)) < abs(left_sum - right_sum)) middle--;

    //    cout << l << " " << middle << " " << r << " " << left_sum << " " << right_sum << endl;

    node* middle_node = new node();
    //повторение алгоритма
    middle_node->left = shennon_fano(l, middle, array);
    middle_node->right = shennon_fano(middle + 1, r, array);

    return middle_node;
}

// Сортировка по частоте использования
void sortByProbability(vector <node>& array) {
    int n = array.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (array[j].frq < array[j + 1].frq) {
                swap(array[j], array[j + 1]);
            }
        }
    }
}

// Создание готовых кодов по дереву
void encode(node* root, string str, unordered_map<char, string>& huffmanCode) {
    if (root == nullptr)
        return;

    // поиск листка
    if (!root->left && !root->right) {
        huffmanCode[root->sym] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

// декодирование закодированной строки
void decode(node* root, int& index, string str) {
    if (root == nullptr) return;

    // лист
    if (!root->left && !root->right) {
        cout << root->sym;
        return;
    }

    index++;

    if (str[index] == '0') decode(root->left, index, str);
    else decode(root->right, index, str);
}


//Хаффман
// узел
struct Node {
    char ch;
    int freq;
    Node* left, * right;
};

// создание нового узла
Node* getNode(char ch, int freq, Node* left, Node* right) {
    Node* node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

// Сравнение символов по частоте упоминания в тексте
struct comp {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Создание готовых кодов по дереву
void encode(Node* root, string str, unordered_map<char, string>& huffmanCode) {
    if (root == nullptr)
        return;

    // поиск листка
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

// Построение дерева 
void buildHuffmanTree(string text) {
    // словарь частотности
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    // приоритетная очередь для выбора листьев
    priority_queue<Node*, vector<Node*>, comp> pq;

    // создание всех листиков
    for (auto pair : freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    // цикл, пока все листья не будут сгруппированы
    while (pq.size() != 1)
    {
        // достать два листа с меньшей встречаемостью
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        // создать новый узел из тех двух с суммой
        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }

    // ссылка на корень дерева
    Node* root = pq.top();

    // кодировка
    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Huffman Codes:" << '\n';
    for (auto pair : huffmanCode) {
        cout << pair.first << " " << pair.second << '\n';
    }

    // вывод строки закодированной
    string str = "";
    for (char ch : text) {
        str += huffmanCode[ch];
    }
    cout << "\nEncoded string:\n" << str << '\n';
    
}

int main() {
    string s = "smurygina viktoriia vladimirovna";
    // создание массива частотности
    vector<node> array;
    bool fl = true;
    for (int i = 0; i < s.size(); i++) {
        // есть ли уже символ в массиве
        fl = true;
        for (node j : array) {
            if (j.sym == s[i]) {
                fl = false;
                break;
            }
        }
        // если символ ещё не встречался
        if (fl) {
            array.emplace_back(s[i], count(s.begin(), s.end(), s[i]));
        }
    }

    // сортировка по встречаемости
    sortByProbability(array);

    cout << "Sorted Array:\n";
    for (int i = 0; i < array.size(); i++) {
        cout << array[i].sym << " " << array[i].frq << endl;
    }

    node* root = shennon_fano(0, array.size() - 1, array);

    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);
    cout << "Shannon-Fano Codes:" << '\n';
    for (auto pair : huffmanCode) {
        cout << pair.first << " " << pair.second << '\n';
    }

    // итоговый закодированный ответ
    string code = "";
    for (char ch : s) {
        code += huffmanCode[ch];
    }
    cout << "\nEncoded string :\n" << code << '\n';

    // декодирование
    int index = -1;
    cout << "\nDecoded string :\n";
    while (index < (int)code.size() - 2) {
        decode(root, index, code);
    }

    // коэффициент сжатия
   // char - 8 бит
    cout << endl << "Compression ratio: " << 8.0 * s.size() / code.size();


    cout << endl;
    cout << endl;
    buildHuffmanTree(s);

    // декодирование
    int index = -1;
    cout << "\nDecoded string :\n";
    while (index < (int)code.size() - 2) {
        decode(root, index, code);
    }

    // коэффициент сжатия
   // char - 8 бит
    cout << endl << "Compression ratio: " << 8.0 * s.size() / code.size();

    return 0;
}