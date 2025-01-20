#include <iomanip>
#include <iostream>
#include <limits>

#include "rndgen.h"

#define MAX_SIZE 40
#define ADD_MENU 1
#define REMOVE_MENU 2
#define FIND_MENU 3
#define EXIT_MENU 4

using std::cin;
using std::cout;
using std::endl;
using std::size_t;

void inputSize(size_t& size);

void inputElem(int& elem);

void generateArray(int* array, const size_t& size, RandomGen& RG);

void menu(unsigned& menupoint);

void show(const int* array, const size_t& size);

void add(int* array, size_t& size, const int& elem);

int findBinarySearch(const int* array, const size_t& size, const int& num);

void remove(int* array, size_t& size, const int& index);

void ShellSort(int* array, const int& size);

int arrayDiffNums(const int* array, const size_t& size);

void wait();

int main() {
    setlocale(LC_ALL, "Russian");

    RandomGen RG;
    int* array = new int[MAX_SIZE];
    size_t size{};

    system("cls");
    inputSize(size);
    generateArray(array, size, RG);

    cout << endl << "--- Исходный массив ---" << endl;
    show(array, size);
    ShellSort(array, size);
    show(array, size);

    wait();

    bool exit_program(false);
    unsigned menupoint{};
    int elem{};
    while (!exit_program) {
        system("cls");
        show(array, size);
        if (size != 0)
            cout << endl << "Кол-во различных чисел в массиве: " << arrayDiffNums(array, size) << endl;
        cout << endl;
        menu(menupoint);
        switch (menupoint) {
            case ADD_MENU:
                try {
                    cout << "Введите новый элемент массива: ";
                    inputElem(elem);
                    add(array, size, elem);
                    cout << "--- Элемент " << elem << " добавлен в массив ---";
                    ShellSort(array, size);
                } catch (const char* str) {
                    cout << str << endl;
                }
                break;
            case REMOVE_MENU:
                if (size == 0)
                    cout << "Массив пуст!" << endl;
                else {
                    cout << "Введите элемент, который хотите удалить: ";
                    inputElem(elem);
                    int foundIndex = findBinarySearch(array, size, elem);
                    if (foundIndex == -1)
                        cout << "Элемент отсутствует в массиве!" << endl;
                    else {
                        do {
                            remove(array, size, foundIndex);
                        } while ((foundIndex = findBinarySearch(array, size, elem)) != -1);
                        cout << "--- Элемент " << elem << " и его дубликаты удалены из массива ---";
                        ShellSort(array, size);
                    }
                }
                break;
            case FIND_MENU:
                if (size == 0)
                    cout << "Массив пуст!" << endl;
                else {
                    cout << "Введите искомый элемент массива: ";
                    inputElem(elem);
                    int foundIndex = findBinarySearch(array, size, elem);
                    if (foundIndex == -1)
                        cout << "Элемент отсутствует в массиве!" << endl;
                    else
                        cout << "Элемент найден по индексу " << foundIndex << endl;
                }
                break;
            case EXIT_MENU:
                exit_program = true;
                cout << endl << "--- Завершение работы программы ---" << endl;
                break;
        }

        if (!exit_program) {
            wait();
        }
    }

    delete[] array;

    return 0;
}

void inputSize(size_t& size) {
    cout << "Введите размер массива (1-20): ";
    cin >> size;
    while (cin.fail() || cin.peek() != '\n' || size < 1 || size > 20) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Некорректные данные. Повторите ввод: ";
        cin >> size;
    }
}

void inputElem(int& elem) {
    cin >> elem;
    while (cin.fail() || cin.peek() != '\n' || elem < -100 || elem > 100) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Некорректные данные. Повторите ввод: ";
        cin >> elem;
    }
}

void generateArray(int* array, const size_t& size, RandomGen& RG) {
    for (size_t i = 0; i < size; ++i) {
        array[i] = RG.rnd(-99, 99);
    }
}

void menu(unsigned& menupoint) {
    cout << "========= МЕНЮ =========" << endl;
    cout << "1. Добавить элемент" << endl;
    cout << "2. Удалить элемент" << endl;
    cout << "3. Поиск элемента" << endl;
    cout << "4. Выход" << endl;
    cout << "Введите пункт меню: ";
    cin >> menupoint;
    while (cin.fail() || cin.peek() != '\n' || menupoint > 4) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Это не пункт меню. Повторите ввод: ";
        cin >> menupoint;
    }
}

void show(const int* array, const size_t& size) {
    cout << "Массив[" << size << (size < 10 ? "]:  " : "]: ");
    for (size_t i = 0; i < size; ++i) cout << std::setw(3) << array[i] << ' ';
    cout << endl << "Индекс:     ";
    for (size_t i = 0; i < size; ++i) cout << std::setw(3) << i << ' ';
}

void add(int* array, size_t& size, const int& elem) {
    if (size == MAX_SIZE) throw "Ошибка: массив переполнен!";
    array[size] = elem;
    size++;
}

int findBinarySearch(const int* array, const size_t& size, const int& num) {
    int left{}, right(size - 1);

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (array[mid] == num) return mid;

        if (array[mid] < num)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

void remove(int* array, size_t& size, const int& index) {
    for (size_t i = index; i < size - 1; ++i) {
        array[i] = array[i + 1];
    }
    size--;
}

void ShellSort(int* array, const int& size) {
    int step, i, j;
    int tmp{};
    int rearrange{}, comparison{};
    step = size / 2;
    while (step > 0) {
        for (i = 0; i < size - step; i++) {
            j = i;
            while (j >= 0) {
                if (array[j] > array[j + step]) {
                    tmp = array[j + step];
                    array[j + step] = array[j];
                    array[j] = tmp;
                    j -= step;  
                    rearrange++;
                } else {
                    j = -1;
                }
                comparison++;
            }
        }
        step /= 2;
    }
    cout << "\n\n --- Массив был отсортирован ---\nПонадобилось сравнений: " << comparison
         << "; перестановок: " << rearrange << endl;
}

int arrayDiffNums(const int* array, const size_t& size) {
    int diffNum = 1;
    for (size_t i = 0; i < size - 1; ++i) {
        if (array[i] != array[i + 1]) diffNum++;
    }
    return diffNum;
}

void wait() {
    getchar();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}