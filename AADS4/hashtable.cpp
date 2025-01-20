#include "hashtable.h"

HashTable::HashTable() : size(0) { cells = new string[capacity]; }

HashTable::~HashTable() {
    for (unsigned i = 0; i < capacity; ++i) delete (cells + i);
    delete[] cells;
}

void HashTable::add(const string& key) {
    if (full()) throw "Ошибка: Хэш-таблица переполнена!";
    int hash = hashFunc(key);
    if (cells[hash] != "") {
        while (cells[hash] != "") hash = (hash + 1) % capacity;
    }
    cells[hash] = key;
    size++;
}

void HashTable::fill(const string* keys, const size_t& keysSize) {
    // cout << size << endl;
    clear();
    // cout << size << endl;
    size_t fillSize = (keysSize > capacity ? capacity : keysSize);
    for (unsigned i = 0; i < fillSize; i++) {
        add(keys[i]);
    }
    // cout << size << endl;
}

void HashTable::remove(const int& hash) {
    if (cells[hash] != "") {
        cells[hash] = "DEL";
        size--;
    }
}

void HashTable::remove(const string& key) {
    int hash = hashFunc(key);
    if (cells[hash] != key) {
        unsigned hashChecked{};
        while (cells[hash] != key) {
            if (hashChecked == capacity - 1 || cells[hash] == "")
                throw "Ошибка: Данный ключ не находится в таблице!";
            hash = (hash + 1) % capacity;
            hashChecked++;
        }
    }
    remove(hash);
}

int HashTable::find(const string& key) const {
    int hash = hashFunc(key);
    if (cells[hash] != key) {
        unsigned hashChecked{};
        while (cells[hash] != key) {
            if (hashChecked == capacity - 1 || cells[hash] == "")
                throw "Ошибка: Данный ключ не находится в таблице!";
            hash = (hash + 1) % capacity;
            hashChecked++;
        }
    }
    return hash;
}

void HashTable::show() const {
    if (size == 0) {
        cout << "Хэш-таблица пуста!" << endl;
    } else {
        for (unsigned i = 0; i < capacity; ++i) {
            if (i % 10 == 0)
                cout << endl
                     << "Хэш:Ключ  | " << std::setw(4) << i << ": " << std::setw(6) << cells[i] << " | ";
            else
                cout << std::setw(4) << i << ": " << std::setw(6) << cells[i] << " | ";
        }
    }
}

int HashTable::hashFunc(const string& key) const {
    int hash{};
    for (char c : key) {
        hash = (hash + c * c) % capacity;
        // cout << c << ' ' << hash << " | ";
    }
    return hash;
}

void HashTable::showRemoveCollision(const int& hash) {
    int collisionCnt = 1;
    for (unsigned i = 0; i < capacity; ++i) {
        if (cells[i] != "" && hash == hashFunc(cells[i])) {
            cout << collisionCnt << ". Хэш: " << i << " Ключ: " << cells[i] << endl;
            collisionCnt++;
        }
    }
    if (collisionCnt == 1) cout << "Не найдено" << endl;
}
