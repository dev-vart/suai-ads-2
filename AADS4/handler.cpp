#include <fstream>
#include <iostream>
#include <limits>
#include <regex>
#include <string>
#include <iomanip>

#include "hashtable.h"
#include "keygen.h"

#define MAX_KEYS 6000
#define FILL_TABLE_MENU 1
#define ADD_CELL_MENU 2
#define DELETE_CELL_MENU 3
#define SHOW_TABLE_MENU 4
#define FIND_CELL_MENU 5
#define COLLISION_TABLE_MENU 6
#define SHOW_BAD_KEYS 7
#define EXIT_MENU 8

#define BY_INDEX 1
#define BY_KEY 2
#define EXIT_TO_MAIN_MENU 3

using std::cin;
using std::cout;
using std::endl;
using std::string;

// ������
std::regex reg("([ABCDEFGHIJKLMNOPQRSTUVWXYZ]{1})([\\d]{3})([ABCDEFGHIJKLMNOPQRSTUVWXYZ]{2})");

void menu(unsigned& menupoint);

void menuDelete(unsigned& menupoint);

void menuFind(unsigned& menupoint);

void inputKeysSize(size_t& keysSize);

void inputKey(string& keyUser);

void inputHash(int& hashUser);

void autoGenerateKeys(KeyGen& KG, string* keys, const size_t& keysSize);

void fillBadKeys(string* keys, string* badKeys, const int& startBadKey, const int& badKeysSize);

void showBadKeys(const string* badKeys, const int& badKeysSize);

int main() {
    setlocale(LC_ALL, "Russian");

    KeyGen KG;
    HashTable HT;
    string* keys = new string[MAX_KEYS];
    string* badKeys = new string[MAX_KEYS];

    unsigned menupoint{};
    bool exit_programm(false);
    size_t keysSize{}, badKeysSize{};
    int hashUser{};
    string keyUser{};
    string filepath = "table.txt";
    std::fstream fs;
    while (!exit_programm) {
        system("cls");
        menu(menupoint);
        cout << endl;
        switch (menupoint) {
            case FILL_TABLE_MENU:
                try {
                    static bool table_filled(false);
                    if (!table_filled) {
                        inputKeysSize(keysSize);
                        autoGenerateKeys(KG, keys, keysSize);
                        HT.fill(keys, keysSize);
                        if (keysSize > HT.getCapacity()) {
                            badKeysSize = keysSize - HT.getCapacity();
                            fillBadKeys(keys, badKeys, HT.getCapacity(), badKeysSize);
                        }
                        table_filled = true;
                        cout << "--- ���-������� ��������� ---" << endl;
                        if (keysSize > HT.getCapacity()) {
                            cout << "--- ��������� ������ ����� ---" << endl;
                        }
                    } else
                        cout << "���-������� ��� ���������!" << endl;
                } catch (const char* str) {
                    cout << str << endl;
                }
                break;
            case ADD_CELL_MENU:
                if (HT.full())
                    cout << "���-������� �����������!" << endl;
                else {
                    inputKey(keyUser);
                    HT.add(keyUser);
                    cout << "--- ���� " << keyUser << " �������� �� ���� " << HT.find(keyUser) << " ---"
                         << endl;
                }
                break;
            case DELETE_CELL_MENU:
                try {
                    if (HT.empty()) {
                        cout << "���-������� �����!" << endl;
                    } else {
                        menuDelete(menupoint);
                        cout << endl;
                        switch (menupoint) {
                            case BY_INDEX:
                                inputHash(hashUser);
                                keyUser = HT.find(hashUser);
                                HT.remove(hashUser);
                                break;
                            case BY_KEY:
                                inputKey(keyUser);
                                hashUser = HT.find(keyUser);
                                HT.remove(keyUser);
                                break;
                            case EXIT_TO_MAIN_MENU:
                                continue;
                                break;
                        }
                        cout << "--- ���� " << keyUser << " �� ���� " << hashUser << " ������ ---" << endl;
                        cout << "--- ��������, ��������� �������� � ��������� ---" << endl;
                        HT.showRemoveCollision(hashUser);
                    }
                } catch (const char* str) {
                    cout << str << endl;
                }
                break;
            case SHOW_TABLE_MENU:
                cout << "=== ���-������� ===" << endl;
                HT.show();
                cout << endl;
                break;
            case FIND_CELL_MENU:
                try {
                    if (HT.empty()) {
                        cout << "���-������� �����!" << endl;
                    } else {
                        menuFind(menupoint);
                        cout << endl;
                        string foundHash;
                        int foundKey{};
                        switch (menupoint) {
                            case BY_INDEX:
                                inputHash(hashUser);
                                foundHash = HT.find(hashUser);
                                if (foundHash == "")
                                    cout << "���� �� ������� ��� ����!" << endl;
                                else
                                    cout << "--- ������ ������� ---" << endl
                                         << "���: " << hashUser << " ����: " << foundHash << endl;
                                break;
                            case BY_KEY:
                                inputKey(keyUser);
                                foundKey = HT.find(keyUser);
                                cout << "--- ������ ������� ---" << endl
                                     << "���: " << foundKey << " ����: " << keyUser << endl;
                                break;
                            case EXIT_TO_MAIN_MENU:
                                continue;
                                break;
                        }
                    }
                } catch (const char* str) {
                    cout << str << endl;
                }
                break;
            case COLLISION_TABLE_MENU:
                fs.open(filepath, std::fstream::out | std::fstream::in | std::fstream::trunc);
                if (!fs.is_open()) cout << "������ �������� �����!" << endl;

                for (int i = 0; i < static_cast<int>(HT.getCapacity()); ++i) {
                    int collisionCnt = 0;
                    for (int j = 0; j < static_cast<int>(HT.getCapacity()); ++j) {
                        if (i == HT.hashFunc(HT.find(j)) && HT.find(j) != "") collisionCnt++;
                    }
                    if (collisionCnt > 0)
                        fs << i << ' ' << collisionCnt << endl;
                    else
                        fs << endl;
                }

                // fs /* << i << "   "*/ << H.arr[i].GetSize() - 1 << "\n";
                // fs /* << i << "   " */ << "0" << "\n";

                fs.close();
                cout << "--- ������ �������� � ���� ---" << endl;
                break;
            case SHOW_BAD_KEYS:
                cout << "=== ������ ����� ===" << endl;
                showBadKeys(badKeys, badKeysSize);
                break;
            case EXIT_MENU:
                cout << "--- ���������� ������ ��������� ---";
                exit_programm = true;
                break;
        }

        if (!exit_programm) {
            getchar();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    delete[] keys;

    return 0;
}

void menu(unsigned& menupoint) {
    cout << "========= ���� =========" << endl;
    cout << "1. ��������� ���-�������" << endl;
    cout << "2. �������� �������" << endl;
    cout << "3. ������� �������" << endl;
    cout << "4. ����� ���-�������" << endl;
    cout << "5. ����� ��������" << endl;
    cout << "6. ������� ��������" << endl;
    cout << "7. �������� ������ �����" << endl;
    cout << "8. �����" << endl;
    cout << "������� ����� ����: ";
    cin >> menupoint;
    while (cin.fail() || cin.peek() != '\n' || menupoint > 8) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "��� �� ����� ����. ��������� ����: ";
        cin >> menupoint;
    }
}

void menuDelete(unsigned& menupoint) {
    cout << "=== ��� ������ ������� ������� ? ===" << endl;
    cout << "1. �� �������/����" << endl;
    cout << "2. �� ��������" << endl;
    cout << "3. ����� � �������� ����" << endl;
    cout << "������� ����� ����: ";
    cin >> menupoint;
    while (cin.fail() || cin.peek() != '\n' || menupoint > 3) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "��� �� ����� ����. ��������� ����: ";
        cin >> menupoint;
    }
}

void menuFind(unsigned& menupoint) {
    cout << "=== ��� ������ ����� ������� ? ===" << endl;
    cout << "1. �� �������/����" << endl;
    cout << "2. �� ��������" << endl;
    cout << "3. ����� � �������� ����" << endl;
    cout << "������� ����� ����: ";
    cin >> menupoint;
    while (cin.fail() || cin.peek() != '\n' || menupoint > 3) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "��� �� ����� ����. ��������� ����: ";
        cin >> menupoint;
    }
}

void inputKeysSize(size_t& keysSize) {
    cout << "������� ���������� ������ ��� ���������(1-6000): ";
    cin >> keysSize;
    while (cin.fail() || cin.peek() != '\n' || keysSize < 1 || keysSize > MAX_KEYS) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "������������ ������. ��������� ����: ";
        cin >> keysSize;
    }
}

void inputKey(string& keyUser) {
    cout << "������� ���� � ������� ������: ";
    cin >> keyUser;
    while (cin.fail() || cin.peek() != '\n' || (std::regex_match(keyUser, reg) == false)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "������������ ������. ��������� ����: ";
        cin >> keyUser;
    }
}

void inputHash(int& hashUser) {
    cout << "������� ���-��������(0-1999): ";
    cin >> hashUser;
    while (cin.fail() || cin.peek() != '\n' || hashUser < 0 || hashUser > 1999) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "������������ ������. ��������� ����: ";
        cin >> hashUser;
    }
}

void autoGenerateKeys(KeyGen& KG, string* keys, const size_t& keysSize) {
    for (int i = 0; i < static_cast<int>(keysSize); i++) {
        keys[i] = KG.generateKey();
    }
}

void fillBadKeys(string* keys, string* badKeys, const int& startBadKey, const int& badKeysSize) {
    for (int i = 0; i < badKeysSize; i++) {
        badKeys[i] = keys[i + startBadKey];
    }
}

void showBadKeys(const string* badKeys, const int& badKeysSize) {
    if (badKeysSize == 0) {
        cout << "��� ������ ������" << endl;
    } else {
        for (int i = 0; i < badKeysSize; i++) {
            if (i % 10 == 0)
                cout << endl
                     << "�����:����  | " << std::setw(4) << i << ": " << std::setw(6) << badKeys[i] << " | ";
            else
                cout << std::setw(4) << i << ": " << std::setw(6) << badKeys[i] << " | ";
        }
    }
}

// if (HT.full()) {
//     cout << "���-������� �����������. ������ ��������� ������ ������� (" << HT.getSize()
//          << " -> " << HT.getSize() * 2 << ") ? " << endl;
// }