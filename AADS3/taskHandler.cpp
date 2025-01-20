#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "queue.h"
#include "stackstruct.h"
#include "task.h"
#include "taskGen.h"

#define MAX_NUMTASK 20
#define MANUAL_GENERATION_MENU 1
#define AUTO_GENERATION_MENU 2

using std::cin;
using std::cout;
using std::endl;

void menu(unsigned& menupoint);

void inputNumTasks(unsigned& numTasks);

void inputTasks(Task& task);

void sortTasks(Task* tasks, unsigned numTasks);

void process(Task* tasks, const unsigned& numTasks, Queue& F, Stack& S0, Stack& S1);

int main() {
    setlocale(LC_ALL, "Russian");
    Stack S0, S1;
    Queue F;
    TaskGen TG;
    Task* tasks = new Task[MAX_NUMTASK];

    unsigned menupoint{}, numTasks{};
    menu(menupoint);
    switch (menupoint) {
        case MANUAL_GENERATION_MENU:
            inputNumTasks(numTasks);
            for (unsigned i = 0; i < numTasks; i++) {
                tasks[i].setName("Задача №" + std::to_string(i + 1));
                inputTasks(tasks[i]);
            }
            break;
        case AUTO_GENERATION_MENU:
            inputNumTasks(numTasks);
            for (unsigned i = 0; i < numTasks; i++) tasks[i] = *(TG.autoGenerateTask(i + 1));
            break;
    }

    sortTasks(tasks, numTasks);

    try {
        process(tasks, numTasks, F, S0, S1);
    } catch (const char*& str) {
        cout << str << endl;
    }

    delete[] tasks;

    return 0;
}

void menu(unsigned& menupoint) {
    cout << "------- МЕНЮ -------" << endl;
    cout << "1. Ввести задачи вручную" << endl;
    cout << "2. Сгенерировать задачи автоматически" << endl;
    cout << "Введите пункт меню: ";
    cin >> menupoint;
    while (cin.fail() || cin.peek() != '\n' || menupoint > 2) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Это не пункт меню. Повторите ввод: ";
        cin >> menupoint;
    }
}

void inputNumTasks(unsigned& numTasks) {
    cout << "Введите количество задач(1-10): ";
    cin >> numTasks;
    while (cin.fail() || cin.peek() != '\n' || numTasks < 1 || numTasks > MAX_NUMTASK) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Некорректные данные. Повторите ввод: ";
        cin >> numTasks;
    }
}

void inputTasks(Task& task) {
    unsigned priority{}, clock{}, duration{};
    cout << "Введите приоритет(0-1), такт поступления(1-20), длительность(1-5): ";
    cin >> priority >> clock >> duration;
    while (cin.fail() || cin.peek() != '\n' || priority > 1 || clock < 1 || clock > 20 || duration < 1 ||
           duration > 5) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Некорректные данные. Повторите ввод: ";
        cin >> priority >> clock >> duration;
    }
    task.setPriority(priority);
    task.setClock(clock);
    task.setDuration(duration);
}

void sortTasks(Task* tasks, unsigned numTasks) {
    std::sort(tasks, tasks + numTasks,
              [](const Task& a, const Task& b) { return a.getClock() < b.getClock(); });
}

void process(Task* tasks, const unsigned& numTasks, Queue& F, Stack& S0, Stack& S1) {
    unsigned curClock = 1, taskIndex = 0, taskTimer = 0;
    bool freeProcessor = true, alltasksdone = false;
    Task* curTask{};

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (!alltasksdone) {
        cout << endl;
        cout << "****************************** ТАКТ " << std::setw(2) << curClock
             << " ******************************" << endl;

        if (taskIndex < numTasks) {
            try {
                while (tasks[taskIndex].getClock() == curClock) {
                    F.add(tasks + taskIndex);
                    taskIndex++;
                }
            } catch (const char*& str) {
                throw;
            }
        }
        cout << endl << "===== Очередь F =====" << endl;
        F.show();

        try {
            while (!F.empty()) {
                if (F.first()->getPriority() == 0)
                    S0.push(F.del());
                else if (F.first()->getPriority() == 1)
                    S1.push(F.del());
            }
        } catch (const char*& str) {
            throw;
        }
        cout << endl << "===== Стек S0 =====" << endl;
        S0.show();
        cout << endl << "===== Стек S1 =====" << endl;
        S1.show();

        try {
            if (freeProcessor) {
                if (!S0.empty()) {
                    curTask = S0.pop();
                    taskTimer = curTask->getDuration();
                    freeProcessor = false;
                } else if (!S1.empty()) {
                    curTask = S1.pop();
                    taskTimer = curTask->getDuration();
                    freeProcessor = false;
                } else if (F.empty() && taskIndex == numTasks) {
                    alltasksdone = true;
                }
            }
        } catch (const char*& str) {
            throw;
        }

        cout << endl << "===== Процессор =====" << endl;
        if (taskTimer > 0) {
            cout << "Выполняется ";
            curTask->show();
            taskTimer--;
        } else {
            cout << "Процессор свободен" << endl;
        }
        if (curTask != 0 && taskTimer == 0) {
            cout << "Выполнена ";
            curTask->show();
            freeProcessor = true;
        }

        if (alltasksdone) cout << endl << "Все задачи обработаны. Система завершена.";

        curClock++;

        getchar();
    }
}

// try {
//     for (unsigned i = 0; i < numTasks; ++i) {
//         F.add(tasks + i);
//     }
// } catch (const char*& str) {
//     cout << str << endl;
//     return 1;
// }
// cout << endl << "===== Очередь F =====" << endl;
// F.show();
// cout << endl;
// F.del();
// F.show();

// try {
//     while (!F.empty()) {
//         if (F.first()->getPriority() == 0)
//             S0.push(F.del());
//         else if (F.first()->getPriority() == 1)
//             S1.push(F.del());
//     }
// } catch (const char*& str) {
//     cout << str << endl;
//     return 2;
// }
// cout << "===== Стек S0 =====" << endl;
// S0.show();
// cout << endl << "===== Стек S1 =====" << endl;
// S1.show();
// cout << endl;

// try {
//     for (unsigned i = 0; i < numTasks; i++) {
//         inputTasks(tasks[i]);
//         tasks[i].setName("Задача №" + std::to_string(i + 1));
//         //tasks[i].show();
//         S0.push(tasks + i);
//     }
//     S0.show();
//     Task* taskex = S0.pop();
//     S0.push(taskex);
//     S0.show();
//     // S0.pop();
//     // S0.pop();
// } catch (const char*& str) {
//     cout << str << endl;
// }
// S0.show();

// try {
//     for (unsigned i = 0; i < numTasks; i++) {
//         inputTasks(tasks[i]);
//         tasks[i].setName("Задача №" + std::to_string(i + 1));
//         // tasks[i].show();
//         F0.add(tasks + i);
//     }
//     F0.show();
//     Task* taskex = F0.del();
//     F0.add(taskex);
//     F0.show();
//     F0.del();
//     F0.del();
// } catch (const char*& str) {
//     cout << str << endl;
// }
// F0.show();

// Task* T1 = new Task("Задача номер 1", 1, 3, 2);
// Task* T2 = TG.autoGenerateTask(2);
// Task* T3 = TG.autoGenerateTask(3);
// Task* T4 = TG.autoGenerateTask(4);
// Task* T5 = TG.autoGenerateTask(5);
// Task* T6 = TG.autoGenerateTask(6);

// S0.push(T1);
// S0.push(T2);
// S0.push(T3);
// S0.push(T4);
// S0.push(T5);

// cout << endl;
// S0.top()->show();

// cout << endl;
// S0.show();

// cout << endl;
// S0.pop();
// S0.show();
// S0.pop();
// S0.show();
// S0.pop();
// S0.show();
// S0.pop();
// S0.show();
// S0.push(T6);
// S0.show();
// S0.pop();
// S0.show();
// S0.pop();

// try {
//     S0.pop();
// } catch (const char* str) {
//     cout << str << endl;
// }

// S0.show();