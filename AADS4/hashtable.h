#pragma once

#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

class HashTable {
   public:
    HashTable();
    ~HashTable();
    void add(const string& key);
    string& find(const int& hash) const { return cells[hash]; }
    int find(const string& key) const;
    void show() const;
    int hashFunc(const string& key) const;
    size_t getCapacity() const { return capacity; };
    bool full() const { return size == capacity; };
    bool empty() const { return size == 0; };
    void remove(const int& hash);
    void remove(const string& key);
    void showRemoveCollision(const int& hash);
    void fill(const string* keys, const size_t& keysSize);

   private:
    string* cells;
    const unsigned capacity = 2000;
    unsigned size{};
    void clear() {
        for (unsigned i = 0; i < capacity; i++) remove(i);
    }
};