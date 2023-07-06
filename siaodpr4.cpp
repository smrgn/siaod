#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct BinTree {
    char value;
    BinTree* left;
    BinTree* right;
};

BinTree* addnode(BinTree* tree, char x) {
    if (tree == NULL) { // Если дерева нет, то формируем корень
        tree = new BinTree; // память под узел
        tree->value = x;   // поле данных
        tree->left = NULL;
        tree->right = NULL; // ветви инициализируем пустотой
    }
    else if (x <= tree->value) {  // условие добавление левого потомка
        tree->left = addnode(tree->left, x);
    }
    else {  // условие добавление правого потомка
        tree->right = addnode(tree->right, x);
    }
    return(tree);
}

BinTree* createTree(int n) {
    vector<char> vec;
    for (int i = 0; i < n; i++) {
        cout << "Enter the " << i + 1 << " value: ";
        char value;
        cin >> value;
        vec.push_back(value);
    }

    cout << "\nWaiting. The tree is created...\n";

    vector<char> v = vec;
    sort(v.begin(), v.end()); //сортируем вектор
    char root = v[v.size() / 2];
    int index = v.size() / 2;
    BinTree* tree = NULL;
    tree = addnode(tree, root);
    vector<char>::iterator position = find(vec.begin(), vec.end(), root);
    if (position != vec.end()) // == vec.end() means the element was not found
        vec.erase(position);
    while (!vec.empty()) {
        tree = addnode(tree, vec[0]);
        vec.erase(vec.begin());
    }

    return tree;
}

void output(BinTree* root, int space = 0) {
    if (!root)
        return;
    enum { COUNT = 2 };
    space += COUNT;
    output(root->right, space);
    for (int i = COUNT; i < space; ++i)
        cout << "  ";
    cout << root->value << endl;
    output(root->left, space);
}

int sumLeaf(BinTree* tree) {
    if (tree == NULL) {
        return 0;
    }
    if (tree->left == NULL && tree->right == NULL) {
        return tree->value;
    }
    int leftPart = sumLeaf(tree->left);
    int rightPart = sumLeaf(tree->right);
    return leftPart + rightPart;
}

int findHeight(BinTree* tree) {
    if (tree == NULL) {
        return 0;
    }
    int leftHeight = findHeight(tree->left);
    int rightHeight = findHeight(tree->right);
    return max(leftHeight, rightHeight) + 1;
}

void reversBypass(BinTree* tree) {
    if (tree == NULL) {
        return;
    }
    reversBypass(tree->left);
    reversBypass(tree->right);
    cout << tree->value << " ";
}

void symmetricBypass(BinTree* tree) {
    if (tree == NULL) {
        return;
    }
    symmetricBypass(tree->left);
    cout << tree->value << " ";
    symmetricBypass(tree->right);
}

int main() {
    BinTree* tree;
    cout << "Do you wanna create the tree yourself or automatically?";
    cout << "\n1) yorself.\n2) automatically.\n";
    int type;
    cin >> type;
    while (type <= 0 || type > 2) {
        cout << "Error. Retype: ";
        cin >> type;
    }
    if (type == 2) {
        tree =
            new BinTree{ 'g',
                new BinTree{'c',
                    new BinTree{'a', 0,
                        new BinTree{'b', 0, 0}
                    },
                    new BinTree{'d', 0,
                        new BinTree{'f', new BinTree{'e', 0, 0}, 0},
                    },
                },
                new BinTree{'i',
                    new BinTree{'h', 0, 0},
                    new BinTree{'k', new BinTree{'j', 0, 0}, new BinTree{'e', 0, 0}},
                },
        };
    }
    else {
        int n;
        cout << "Enter the amount of values: ";
        cin >> n;
        while (n <= 0) {
            cout << "Error. Retype: ";
            cin >> n;
        }
        tree = createTree(n);
    }

    cout << "\n---Tree---" << endl;
    output(tree);
    
    int exc = 1;
    while (exc != 0) {
        cout << "Choose what you wanna do: \n";
        cout << "1) Find height;\n" << "2) Find leaf sum;\n";
        cout << "3) Make a revers bypass;\n" << "4) Make a symmetric bypass;\n";
        cout << "5) Add item;\n" << "0) for exit.\n";
        cin >> exc;
        while (exc < 0 || exc > 5) {
            cout << "Error. Retype: ";
            cin >> exc;
        }
        switch (exc) {
        case 1: {
            cout << "Height: " << findHeight(tree) << endl;
            break;
        }
        case 2: {
            cout << "Sum of leaves: " << sumLeaf(tree) << endl;
            break;
        }
        case 3: {
            cout << "Revers Bypass: ";
            reversBypass(tree);
            cout << endl;
            break;
        }
        case 4: {
            cout << "Symmetric Bypass: ";
            symmetricBypass(tree);
            cout << endl;
            break;
        }
        case 5: {
            cout << "Enter item which you wanna add: ";
            char item;
            cin >> item;
            addnode(tree, item);

            cout << "\n---Tree---" << endl;
            output(tree);
            break;
        }
        case 0: {
            cout << "Program is ending....";
            break;
        }
        }
    }
    return 0;
}
