#pragma once

#include <algorithm>
#include <exception>
#include <iomanip>
#include <iostream>

#include "rndgen.h"

using std::cout;
using std::endl;
using std::max;
using std::string;

class Node {
   public:
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int value) : key(value), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
   private:
    RandomGen randomgen;
    Node* root;
    int getHeight(Node* node) const { return node ? node->height : 0; }
    int getBalance(Node* node) const { return node ? getHeight(node->left) - getHeight(node->right) : 0; }
    Node* insertNode(Node* node, int key);
    Node* searchNode(Node* node, int key, int& stepCount) const;
    Node* removeNode(Node* node, int key);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* balance(Node* node);
    void inorderTraversal(Node* node) const;
    void deleteTree(Node* node);
    void show(Node* node, int level) const;
    void countMean(Node* node, double& sum, double& leafCount) const;
    void subtractMean(Node* node, double& mean);
    void removeAllMult3(Node* node);

   public:
    AVLTree() : root(nullptr), randomgen() {}
    ~AVLTree() { deleteTree(root); }
    bool empty() const { return root == nullptr; };
    void insert(int key) { root = insertNode(root, key); }
    void remove(int key) { root = removeNode(root, key); }
    int search(int key) const;
    void display() const;
    void fill(int count);
    void traversal();
    double countMeanLeaves();
    void subtractMeanLeaves(double& mean);
    void removeTask();
};

double AVLTree::countMeanLeaves() {
    double sum = 0, leafCount = 0;
    countMean(root, sum, leafCount);
    return sum / leafCount;
}

void AVLTree::removeTask() { removeAllMult3(root); }

void AVLTree::removeAllMult3(Node* node) {
    if (node != nullptr) {
        removeAllMult3(node->left);
        if (node->key % 3 == 0) {
            removeNode(node, node->key);
        }
        removeAllMult3(node->right);
    }
}

void AVLTree::subtractMeanLeaves(double& mean) { subtractMean(root, mean); }

void AVLTree::traversal() { inorderTraversal(root); }

void AVLTree::fill(int count) {
    while (count > 0) {
        insert(randomgen.rnd(0, 100));
        count--;
    }
}

int AVLTree::search(int key) const {
    int stepCount = 0;
    if (searchNode(root, key, stepCount) != nullptr) {
        return stepCount;
    } else
        return -1;
}

void AVLTree::display() const {
    if (!empty()) {
        cout << "------------------------------------" << endl;
        show(root, 0);
        cout << "------------------------------------" << endl;
    } else
        cout << "Дерево пусто" << endl;
}

void AVLTree::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->right;  // y - heavy node
    Node* Y1 = y->left;

    y->left = x;  // left rotation
    x->right = Y1;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

Node* AVLTree::rightRotate(Node* x) {
    Node* y = x->left;  // y - heavy node
    Node* Y2 = y->right;

    y->right = x;  // right rotation
    x->left = Y2;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

Node* AVLTree::balance(Node* node) {
    int balanceFactor = getBalance(node);

    // left-heavy
    if (balanceFactor > 1) {
        // Малый правый поворот
        if (getBalance(node->left) >= 0) {
            return rightRotate(node);
        }
        // Большой правый поворот (Левый - правый поворот)
        else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    // right-heavy
    if (balanceFactor < -1) {
        // Малый левый поворот
        if (getBalance(node->right) <= 0) {
            return leftRotate(node);
        }
        // Большой левый поворот (Правый - левый поворот)
        else {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

Node* AVLTree::insertNode(Node* node, int key) {
    if (node == nullptr) {
        return new Node(key);
    }
    if (key < node->key) {
        node->left = insertNode(node->left, key);
    } else if (key > node->key) {
        node->right = insertNode(node->right, key);
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    return balance(node);
}

Node* AVLTree::searchNode(Node* node, int key, int& stepCount) const {
    stepCount++;
    if (node == nullptr || node->key == key) {
        return node;  // Узел найден или достигнут конец дерева
    }

    if (key < node->key) {
        return searchNode(node->left, key, stepCount);
    } else {
        return searchNode(node->right, key, stepCount);
    }
}

Node* AVLTree::removeNode(Node* node, int key) {
    if (node == nullptr) return node;

    if (key < node->key)
        node->left = removeNode(node->left, key);
    else if (key > node->key)
        node->right = removeNode(node->right, key);
    else {
        // Узел найден
        Node* temp;
        int childrenCount = (node->left != nullptr) + (node->right != nullptr);
        if (childrenCount == 0) {
            temp = node;
            node = nullptr;
            delete temp;
        } else if (childrenCount == 1) {
            temp = node->left ? node->left : node->right;
            *node = *temp;
            delete temp;
        } else {
            // Находим минимальный узел в правом поддереве
            temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }

            node->key = temp->key;

            node->right = removeNode(node->right, temp->key);
        }
    }

    if (node == nullptr) return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    return balance(node);
}

void AVLTree::show(Node* node, int level) const {
    if (node) {
        show(node->right, level + 1);
        cout << string(level * 4, ' ') << "< " << node->key << endl;
        show(node->left, level + 1);
    }
}

void AVLTree::inorderTraversal(Node* node) const {
    if (node != nullptr) {
        inorderTraversal(node->left);
        std::cout << std::setw(4) << node->key << " ";
        inorderTraversal(node->right);
    }
}

void AVLTree::countMean(Node* node, double& sum, double& leafCount) const {
    int childrenCount = 0;
    if (node != nullptr) {
        countMean(node->left, sum, leafCount);
        if (node->left == nullptr && node->right == nullptr) {
            sum += node->key;
            leafCount++;
        }
        countMean(node->right, sum, leafCount);
    }
}

void AVLTree::subtractMean(Node* node, double& mean) {
    if (node != nullptr) {
        subtractMean(node->left, mean);
        if (node->left == nullptr && node->right == nullptr) {
            node->key = node->key - mean;
        }
        subtractMean(node->right, mean);
    }
}
