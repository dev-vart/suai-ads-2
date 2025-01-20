#include <iomanip>
#include <iostream>
#include <limits>

#include "AVLTree.h"

#define NEW_TREE 1
#define AUTO_GENERATE_TREE 2

#define ADD_MENU 1
#define REMOVE_MENU 2
#define FIND_MENU 3
#define ROUND_MENU 4
#define TASK_MENU 5
#define EXIT_MENU 6

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

void inputElem(int& elem);

void inputSize(int& size);

void menu(unsigned& menupoint);

void genMenu(unsigned& menupoint);

void wait();

int main() {
    setlocale(LC_ALL, "Russian");

    system("cls");

    AVLTree avlt;
    int size{};

    unsigned menupoint{};
    genMenu(menupoint);
    switch (menupoint) {
        case NEW_TREE:
            break;
        case AUTO_GENERATE_TREE:
            inputSize(size);
            avlt.fill(size);
            break;
    }

    cout << endl << "==== Исходное дерево ====" << endl;
    avlt.display();

    wait();

    bool exit_programm(false);
    int elem{};
    while (!exit_programm) {
        system("cls");
        cout << endl << "==== Дерево ====" << endl;
        avlt.display();
        cout << endl;
        menu(menupoint);
        cout << endl;
        switch (menupoint) {
            case ADD_MENU:
                cout << "Введите новый элемент дерева(-100-100): ";
                inputElem(elem);
                if (avlt.search(elem) > 0)
                    cerr << endl << "Ошибка: Элемент " << elem << " уже есть в дереве!" << endl;
                else {
                    avlt.insert(elem);
                    cout << endl << "--- Элемент " << elem << " добавлен в дерево ---" << endl;
                    avlt.display();
                }
                break;
            case REMOVE_MENU:
                cout << "Введите элемент дерева(-100-100): ";
                inputElem(elem);
                if (avlt.empty())
                    cout << endl << "Дерево пусто!" << endl;
                else if (avlt.search(elem) == -1)
                    cerr << endl << "Ошибка: Элемента " << elem << " нет в дереве!" << endl;
                else {
                    avlt.remove(elem);
                    cout << endl << "--- Элемент " << elem << " удален из дерева ---" << endl;
                    avlt.display();
                }
                break;
            case FIND_MENU:
                if (avlt.empty())
                    cout << endl << "Дерево пусто!" << endl;
                else {
                    cout << "Введите искомый элемент дерева: ";
                    inputElem(elem);
                    if (avlt.search(elem) > 0)
                        cout << "Элемент найден в дереве" << endl;
                    else
                        cout << "Элемент отсутствует в дереве" << endl;
                }
                break;
            case ROUND_MENU:
                if (avlt.empty())
                    cout << endl << "Дерево пусто!" << endl;
                else {
                    cout << "==== Обход дерева ====" << endl;
                    avlt.traversal();
                }
                break;
            case TASK_MENU:
                if (avlt.empty())
                    cout << endl << "Дерево пусто!" << endl;
                else {
                    cout << "==== Задание ====" << endl;
                    double mean = avlt.countMeanLeaves();
                    cout << "Среднее арифметическое всех листов дерева: " << mean << endl;
                    avlt.subtractMeanLeaves(mean);
                    cout << "Вычтем среднее арифметическое из всех листов дерева: " << endl;
                    avlt.display();
                    cout << "Удалим все элементы дерева, кратные 3: " << endl;
                    avlt.removeTask();
                    avlt.display();
                }
                break;
            case EXIT_MENU:
                exit_programm = true;
                cout << endl << "--- Завершение работы программы ---" << endl;
                break;
        }

        if (!exit_programm) {
            wait();
        }
    }
    return 0;
}

void inputSize(int& size) {
    cout << "Введите кол-во элементов (1-10): ";
    cin >> size;
    while (cin.fail() || cin.peek() != '\n' || size < 1 || size > 10) {
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

void genMenu(unsigned& menupoint) {
    cout << "Как вы хотите создать дерево?" << endl;
    cout << "1. С нуля" << endl;
    cout << "2. Заполнить случайными значениями" << endl;
    cout << "Введите пункт меню: ";
    cin >> menupoint;
    while (cin.fail() || cin.peek() != '\n' || menupoint > 2) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Это не пункт меню. Повторите ввод: ";
        cin >> menupoint;
    }
}

void menu(unsigned& menupoint) {
    cout << "========= МЕНЮ =========" << endl;
    cout << "1. Добавить элемент" << endl;
    cout << "2. Удалить элемент" << endl;
    cout << "3. Поиск элемента" << endl;
    cout << "4. Обход вершин" << endl;
    cout << "5. Задание варианта" << endl;
    cout << "6. Выход" << endl;
    cout << "Введите пункт меню: ";
    cin >> menupoint;
    while (cin.fail() || cin.peek() != '\n' || menupoint > 6) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Это не пункт меню. Повторите ввод: ";
        cin >> menupoint;
    }
}

void wait() {
    getchar();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}