#pragma once

#include <iostream>

#include "task.h"

#define MAX_QUEUE_SIZE 10

class Queue {
   public:
    Queue();
    bool empty() const;
    bool full() const;
    void add(Task* val);
    Task* del();
    const Task* first() const;
    const Task* last() const;
    void show() const;

   private:
    Task* queue[MAX_QUEUE_SIZE];
    int size{};
    int headIndex;
    int tailIndex;
};
