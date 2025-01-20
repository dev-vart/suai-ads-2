#pragma once

#include <iostream>

#include "task.h"

#define MAX_STACK_SIZE 10

class Stack {
   public:
    Stack();
    ~Stack();
    bool empty() const;
    bool full() const;
    void push(Task* val);
    const Task* top() const;
    Task* pop();
    void show() const;

   private:
    unsigned size{};
    struct Node {
        Task* data;
        Node* next;
    };
    Node* root;
};
