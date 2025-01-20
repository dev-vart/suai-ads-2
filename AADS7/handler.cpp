#include <iomanip>
#include <iostream>
#include <limits>

#include "graph.h"

#define ADD_MENU 1
#define REMOVE_MENU 2
#define EULERIAN_CYCLE_MENU 3
#define EXIT_MENU 4

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

void inputElem(char& elem1);

void inputElem2(char& elem1, char& elem2);

void menu(unsigned& menupoint);

void wait();

int main() {
    setlocale(LC_ALL, "Russian");

    system("cls");

    Graph G(5);

    unsigned menupoint{};

    G.addEdge('A', 'B');
    G.addEdge('A', 'C');
    G.addEdge('A', 'D');
    G.addEdge('A', 'E');
    G.addEdge('B', 'C');
    G.addEdge('B', 'D');
    G.addEdge('B', 'E');
    G.addEdge('C', 'D');
    G.addEdge('C', 'E');
    G.addEdge('D', 'E');

    bool exit_programm(false);
    char vert1{}, vert2{};
    while (!exit_programm) {
        system("cls");
        cout << endl << "==== ������� ��������� ����� ====" << endl;
        G.show();
        cout << endl;
        menu(menupoint);
        cout << endl;
        switch (menupoint) {
            case ADD_MENU:
                try {
                    cout << "������� ��� ������� ������ ����� ������ (��������, AB): ";
                    inputElem2(vert1, vert2);
                    G.addEdge(vert1, vert2);
                    cout << endl << "����� " << vert1 << vert2 << " ���������" << endl;
                } catch (std::exception& e) {
                    cout << e.what() << endl;
                } catch (...) {
                    cout << "����������� ����������" << endl;
                }
                break;
            case REMOVE_MENU:
                try {
                    cout << "������� ��� ������� �����, ������� ������ �������, ������ (��������, AB): ";
                    inputElem2(vert1, vert2);
                    G.removeEdge(vert1, vert2);
                    cout << endl << "����� " << vert1 << vert2 << " �������" << endl;
                } catch (std::exception& e) {
                    cout << e.what() << endl;
                } catch (...) {
                    cout << "����������� ����������" << endl;
                }
                break;
            case EULERIAN_CYCLE_MENU:
                cout << "������� ��������� ������� ���������� �����: ";
                inputElem(vert1);
                G.printEulerianCycle(vert1);
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

void menu(unsigned& menupoint) {
    cout << "========= ���� =========" << endl;
    cout << "1. �������� �����" << endl;
    cout << "2. ������� �����" << endl;
    cout << "3. ������� ������� ����" << endl;
    cout << "4. �����" << endl;
    cout << "������� ����� ����: ";
    cin >> menupoint;
    while (cin.fail() || cin.peek() != '\n' || menupoint > 4) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "��� �� ����� ����. ��������� ����: ";
        cin >> menupoint;
    }
}

void inputElem(char& elem1) {
    cin >> elem1;
    while (cin.fail() || cin.peek() != '\n' || elem1 < 'A' || elem1 > 'Z') {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "������������ ������. ��������� ����: ";
        cin >> elem1;
    }
}

void inputElem2(char& elem1, char& elem2) {
    cin >> elem1 >> elem2;
    while (cin.fail() || cin.peek() != '\n' || elem1 < 'A' || elem1 > 'Z' || elem2 < 'A' || elem2 > 'Z') {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "������������ ������. ��������� ����: ";
        cin >> elem1 >> elem2;
    }
}

void wait() {
    getchar();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}