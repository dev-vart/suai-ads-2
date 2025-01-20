#include "stackstruct.h"

Stack::Stack() : size(0), root(nullptr) {}  // �� ��������� ���� ����

Stack::~Stack() {
    while (!empty()) {
        Node* delnode = root;
        root = root->next;
        delete delnode;
    }
}

bool Stack::empty() const { return root == nullptr; }  // ���� ������ nullptr �� ���� ����

bool Stack::full() const { return size == MAX_STACK_SIZE; }

void Stack::push(Task* val) {
    if (full()) throw "������ � ������� push(): ���� ����������!";
    Node* newnode = new Node;  // ������� ����� ����
    newnode->data = val;       // ���������� ������
    newnode->next = root;      // next ������ �������� ����� ������� ����
    root = newnode;            // ��������� root
    size++;
}

const Task* Stack::top() const {
    if (empty()) throw "������ � ������� top(): ���� ����!";
    return root->data;
}

Task* Stack::pop() {
    if (empty()) throw "������ � ������� pop(): ���� ����!";
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
        std::cout << "���������� �����:" << std::endl;
        while (current != nullptr) {
            current->data->show();
            current = current->next;
        }
    } else {
        std::cout << "���� ����" << std::endl;
    }
}

// void Stack::pop() {
//     if (empty()) throw "������ � ������� pop(): ���� ����";
//     Node* delnode = root;  // ���� ������� ���� �������
//     root = root->next;     // ��������� root
//     delete delnode;
// }
