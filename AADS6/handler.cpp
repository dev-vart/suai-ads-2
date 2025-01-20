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

    cout << endl << "==== �������� ������ ====" << endl;
    avlt.display();

    wait();

    bool exit_programm(false);
    int elem{};
    while (!exit_programm) {
        system("cls");
        cout << endl << "==== ������ ====" << endl;
        avlt.display();
        cout << endl;
        menu(menupoint);
        cout << endl;
        switch (menupoint) {
            case ADD_MENU:
                cout << "������� ����� ������� ������(-100-100): ";
                inputElem(elem);
                if (avlt.search(elem) > 0)
                    cerr << endl << "������: ������� " << elem << " ��� ���� � ������!" << endl;
                else {
                    avlt.insert(elem);
                    cout << endl << "--- ������� " << elem << " �������� � ������ ---" << endl;
                    avlt.display();
                }
                break;
            case REMOVE_MENU:
                cout << "������� ������� ������(-100-100): ";
                inputElem(elem);
                if (avlt.empty())
                    cout << endl << "������ �����!" << endl;
                else if (avlt.search(elem) == -1)
                    cerr << endl << "������: �������� " << elem << " ��� � ������!" << endl;
                else {
                    avlt.remove(elem);
                    cout << endl << "--- ������� " << elem << " ������ �� ������ ---" << endl;
                    avlt.display();
                }
                break;
            case FIND_MENU:
                if (avlt.empty())
                    cout << endl << "������ �����!" << endl;
                else {
                    cout << "������� ������� ������� ������: ";
                    inputElem(elem);
                    if (avlt.search(elem) > 0)
                        cout << "������� ������ � ������" << endl;
                    else
                        cout << "������� ����������� � ������" << endl;
                }
                break;
            case ROUND_MENU:
                if (avlt.empty())
                    cout << endl << "������ �����!" << endl;
                else {
                    cout << "==== ����� ������ ====" << endl;
                    avlt.traversal();
                }
                break;
            case TASK_MENU:
                if (avlt.empty())
                    cout << endl << "������ �����!" << endl;
                else {
                    cout << "==== ������� ====" << endl;
                    double mean = avlt.countMeanLeaves();
                    cout << "������� �������������� ���� ������ ������: " << mean << endl;
                    avlt.subtractMeanLeaves(mean);
                    cout << "������ ������� �������������� �� ���� ������ ������: " << endl;
                    avlt.display();
                    cout << "������ ��� �������� ������, ������� 3: " << endl;
                    avlt.removeTask();
                    avlt.display();
                }
                break;
            case EXIT_MENU:
                exit_programm = true;
                cout << endl << "--- ���������� ������ ��������� ---" << endl;
                break;
        }

        if (!exit_programm) {
            wait();
        }
    }
    return 0;
}

void inputSize(int& size) {
    cout << "������� ���-�� ��������� (1-10): ";
    cin >> size;
    while (cin.fail() || cin.peek() != '\n' || size < 1 || size > 10) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "������������ ������. ��������� ����: ";
        cin >> size;
    }
}

void inputElem(int& elem) {
    cin >> elem;
    while (cin.fail() || cin.peek() != '\n' || elem < -100 || elem > 100) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "������������ ������. ��������� ����: ";
        cin >> elem;
    }
}

void genMenu(unsigned& menupoint) {
    cout << "��� �� ������ ������� ������?" << endl;
    cout << "1. � ����" << endl;
    cout << "2. ��������� ���������� ����������" << endl;
    cout << "������� ����� ����: ";
    cin >> menupoint;
    while (cin.fail() || cin.peek() != '\n' || menupoint > 2) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "��� �� ����� ����. ��������� ����: ";
        cin >> menupoint;
    }
}

void menu(unsigned& menupoint) {
    cout << "========= ���� =========" << endl;
    cout << "1. �������� �������" << endl;
    cout << "2. ������� �������" << endl;
    cout << "3. ����� ��������" << endl;
    cout << "4. ����� ������" << endl;
    cout << "5. ������� ��������" << endl;
    cout << "6. �����" << endl;
    cout << "������� ����� ����: ";
    cin >> menupoint;
    while (cin.fail() || cin.peek() != '\n' || menupoint > 6) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "��� �� ����� ����. ��������� ����: ";
        cin >> menupoint;
    }
}

void wait() {
    getchar();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}