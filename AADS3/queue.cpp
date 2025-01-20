#include "queue.h"

Queue::Queue() : size(0), headIndex(0), tailIndex(-1) {}

bool Queue::empty() const { return size == 0; }

bool Queue::full() const { return size == MAX_QUEUE_SIZE; }

void Queue::add(Task* val) {
    if (full()) throw "������ � ������� add(): ������� �����������!";
    tailIndex = (tailIndex + 1) % MAX_QUEUE_SIZE;  // ��������� �����
    queue[tailIndex] = val;                        // ���������� ������
    size++;                                        // ����������� ������
}

const Task* Queue::first() const {
    if (empty()) throw "������ � ������� first(): ������� �����!";
    return queue[headIndex];
}

const Task* Queue::last() const {
    if (empty()) throw "������ � ������� last(): ������� �����!";
    return queue[tailIndex];
}

Task* Queue::del() {
    if (empty()) throw "������ � ������� del(): ������� �����!";

    Task* res = queue[headIndex];                  // ��������� ������
    headIndex = (headIndex + 1) % MAX_QUEUE_SIZE;  // ��������� ������
    size--;                                        // ��������� ������
    return res;
}

void Queue::show() const {
    if (!empty()) {
        std::cout << "���������� �������:" << std::endl;
        for (int i = 0; i < size; i++) {
            int curIndex = (headIndex + i) % MAX_QUEUE_SIZE;
            queue[curIndex]->show();
        }
    } else {
        std::cout << "������� �����" << std::endl;
    }
}
