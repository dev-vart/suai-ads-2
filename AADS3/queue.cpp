#include "queue.h"

Queue::Queue() : size(0), headIndex(0), tailIndex(-1) {}

bool Queue::empty() const { return size == 0; }

bool Queue::full() const { return size == MAX_QUEUE_SIZE; }

void Queue::add(Task* val) {
    if (full()) throw "Ошибка в функции add(): Очередь переполнена!";
    tailIndex = (tailIndex + 1) % MAX_QUEUE_SIZE;  // обновляем хвост
    queue[tailIndex] = val;                        // записываем данные
    size++;                                        // увеличиваем размер
}

const Task* Queue::first() const {
    if (empty()) throw "Ошибка в функции first(): Очередь пуста!";
    return queue[headIndex];
}

const Task* Queue::last() const {
    if (empty()) throw "Ошибка в функции last(): Очередь пуста!";
    return queue[tailIndex];
}

Task* Queue::del() {
    if (empty()) throw "Ошибка в функции del(): Очередь пуста!";

    Task* res = queue[headIndex];                  // сохраняем данные
    headIndex = (headIndex + 1) % MAX_QUEUE_SIZE;  // обновляем голову
    size--;                                        // уменьшаем размер
    return res;
}

void Queue::show() const {
    if (!empty()) {
        std::cout << "Содержимое очереди:" << std::endl;
        for (int i = 0; i < size; i++) {
            int curIndex = (headIndex + i) % MAX_QUEUE_SIZE;
            queue[curIndex]->show();
        }
    } else {
        std::cout << "Очередь пуста" << std::endl;
    }
}
