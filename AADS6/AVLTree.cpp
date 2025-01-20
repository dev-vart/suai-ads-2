// #include "AVLTree.h"

// #include <algorithm>
// #include <iostream>

// #include "rndgen.h"

// using std::cout;
// using std::endl;
// using std::max;
// using std::string;

// class Node {
//    public:
//     int key;
//     Node* left;
//     Node* right;
//     int height;

//     Node(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
// };

// class AVLTree {
//    private:
//     RandomGen randomgen;
//     Node* root;
//     int getHeight(Node* node) const { return node ? node->height : 0; }
//     int getBalance(Node* node) const { return node ? getHeight(node->left) - getHeight(node->right) : 0; }
//     Node* insertNode(Node* node, int key);
//     Node* searchNode(Node* node, int key, int& stepCount) const;
//     Node* removeNode(Node* node, int key);
//     Node* rightRotate(Node* y);
//     Node* leftRotate(Node* x);
//     Node* balance(Node* node);
//     void deleteTree(Node* node);
//     void show(Node* node, int level) const;

//    public:
//     AVLTree() : root(nullptr), randomgen() {}
//     ~AVLTree() { deleteTree(root); }
//     bool empty() const { return root == nullptr; };
//     void insert(int key) { root = insertNode(root, key); }
//     void remove(int key) { root = removeNode(root, key); }
//     int search(int key) const;
//     void display() const;
//     void fill(int count);
// };

// void AVLTree::fill(int count) {
//     while (count > 0) {
//         insert(randomgen.rnd(0, 100));
//         count--;
//     }
// }

// int AVLTree::search(int key) const {
//     int stepCount = 0;
//     if (searchNode(root, key, stepCount) != nullptr) {
//         return stepCount;
//     } else
//         return -1;
// }

// void AVLTree::display() const {
//     if (!empty()) {
//         cout << "------------------------------------" << endl;
//         show(root, 0);
//         cout << "------------------------------------" << endl;
//     } else
//         cout << "Дерево пусто" << endl;
// }

// void AVLTree::deleteTree(Node* node) {
//     if (node) {
//         deleteTree(node->left);
//         deleteTree(node->right);
//         delete node;
//     }
// }

// Node* AVLTree::leftRotate(Node* x) {
//     Node* y = x->right;  // y - heavy node
//     Node* Y1 = y->left;

//     y->left = x;  // left rotation
//     x->right = Y1;

//     x->height = 1 + max(getHeight(x->left), getHeight(x->right));
//     y->height = 1 + max(getHeight(y->left), getHeight(y->right));

//     return y;
// }

// Node* AVLTree::rightRotate(Node* x) {
//     Node* y = x->left;  // y - heavy node
//     Node* Y2 = y->right;

//     y->right = x;  // right rotation
//     x->left = Y2;

//     x->height = 1 + max(getHeight(x->left), getHeight(x->right));
//     y->height = 1 + max(getHeight(y->left), getHeight(y->right));

//     return y;
// }

// Node* AVLTree::balance(Node* node) {
//     int balanceFactor = getBalance(node);

//     // left-heavy
//     if (balanceFactor > 1) {
//         // Малый правый поворот
//         if (getBalance(node->left) >= 0) {
//             return rightRotate(node);
//         }
//         // Большой правый поворот (Левый - правый поворот)
//         else {
//             node->left = leftRotate(node->left);
//             return rightRotate(node);
//         }
//     }
//     // right-heavy
//     if (balanceFactor < -1) {
//         // Малый левый поворот
//         if (getBalance(node->right) <= 0) {
//             return leftRotate(node);
//         }
//         // Большой левый поворот (Правый - левый поворот)
//         else {
//             node->right = rightRotate(node->right);
//             return leftRotate(node);
//         }
//     }

//     return node;
// }

// Node* AVLTree::insertNode(Node* node, int key) {
//     if (!node) {
//         return new Node(key);
//     }
//     if (key < node->key) {
//         node->left = insertNode(node->left, key);
//     } else {
//         node->right = insertNode(node->right, key);
//     }

//     node->height = 1 + max(getHeight(node->left), getHeight(node->right));

//     return balance(node);
// }

// Node* AVLTree::searchNode(Node* node, int key, int& stepCount) const {
//     stepCount++;
//     if (node == nullptr || node->key == key) {
//         return node;  // Узел найден или достигнут конец дерева
//     }

//     if (key < node->key) {
//         return searchNode(node->left, key, stepCount);
//     } else {
//         return searchNode(node->right, key, stepCount);
//     }
// }

// Node* AVLTree::removeNode(Node* node, int key) {
//     if (node == nullptr) return node;

//     if (key < node->key)
//         node->left = removeNode(node->left, key);
//     else if (key > node->key)
//         node->right = removeNode(node->right, key);
//     else {
//         // Узел найден
//         Node* temp;
//         int childrenCount = (node->left != nullptr) + (node->right != nullptr);
//         if (childrenCount == 0) {
//             temp = node;
//             node = nullptr;
//             delete temp;
//         } else if (childrenCount == 1) {
//             temp = node->left ? node->left : node->right;
//             *node = *temp;
//             delete temp;
//         } else {
//             // Находим минимальный узел в правом поддереве
//             temp = node->right;
//             while (temp->left != nullptr) {
//                 temp = temp->left;
//             }

//             node->key = temp->key;

//             node->right = removeNode(node->right, temp->key);
//         }
//     }

//     if (node == nullptr) return node;

//     node->height = 1 + max(getHeight(node->left), getHeight(node->right));

//     return balance(node);
// }

// void AVLTree::show(Node* node, int level) const {
//     if (node) {
//         show(node->right, level + 1);
//         cout << string(level * 4, ' ') << "< " << node->key << endl;
//         show(node->left, level + 1);
//     }
// }

// int main() {
//     AVLTree avl;

//     avl.fill(10);

//     cout << endl << avl.search(30) << endl << endl;

//     avl.display();

//     avl.remove(40);

//     avl.display();

//     avl.insert(32);

//     avl.display();

//     return 0;
// }

// // if (!node->left || !node->right) {
// // Узел с одним дочерним узлом или без дочерних узлов
// // Node* temp = node->left ? node->left : node->right;

// // if (!temp) {
// //         // Узел — лист
// //         temp = node;
// //         node = nullptr;  // Удаляем узел
// //     } else {
// //         // Узел имеет одного дочернего узла
// //         *node = *temp;  // Копируем содержимое дочернего узла
// //     }
// //     delete temp;  // Освобождаем память
// // }

// // else {
// //     // Узел с двумя дочерними узлами
// //     // Находим минимальный узел в правом поддереве
// //     Node* temp = node->right;
// //     while (temp->left) {
// //         temp = temp->left;
// //     }

// //     // Копируем значение минимального узла в текущий узел
// //     node->key = temp->key;

// //     // Удаляем минимальный узел
// //     node->right = removeNode(node->right, temp->key);
// // }