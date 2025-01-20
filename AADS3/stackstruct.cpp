#include "stackstruct.h"

Stack::Stack() : size(0), root(nullptr) {}  // по умолчанию стек пуст

Stack::~Stack() {
    while (!empty()) {
        Node* delnode = root;
        root = root->next;
        delete delnode;
    }
}

bool Stack::empty() const { return root == nullptr; }  // если голова nullptr то стек пуст

bool Stack::full() const { return size == MAX_STACK_SIZE; }

void Stack::push(Task* val) {
    if (full()) throw "Ошибка в функции push(): Стек переполнен!";
    Node* newnode = new Node;  // создаем новый узел
    newnode->data = val;       // записываем данные
    newnode->next = root;      // next нового элемента равен старому узлу
    root = newnode;            // обновляем root
    size++;
}

const Task* Stack::top() const {
    if (empty()) throw "Ошибка в функции top(): Стек пуст!";
    return root->data;
}

Task* Stack::pop() {
    if (empty()) throw "Ошибка в функции pop(): Стек пуст!";
    Node* delnode = root;
    Task* res = delnode->data;
    root = root->next;
    delete delnode;
    size--;
    return res;
}

void Stack::show() const {
    if (!empty()) {
        Node* current = root;
        std::cout << "Содержимое стека:" << std::endl;
        while (current != nullptr) {
            current->data->show();
            current = current->next;
        }
    } else {
        std::cout << "Стек пуст" << std::endl;
    }
}

// void Stack::pop() {
//     if (empty()) throw "Ошибка в функции pop(): Стек пуст";
//     Node* delnode = root;  // узел который надо удалить
//     root = root->next;     // обновляем root
//     delete delnode;
// }
