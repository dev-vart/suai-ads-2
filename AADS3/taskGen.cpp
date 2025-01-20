#include "taskGen.h"

#include "task.h"

Task* TaskGen::autoGenerateTask(unsigned inputTime) {
    unsigned clock{}, duration{}, priority{};

    string name = "������ �" + std::to_string(inputTime);
    clock = randomGen.rnd(1, 10);
    priority = randomGen.rnd(0, 1);
    duration = randomGen.rnd(1, 5);

    Task* task = new Task(name, priority, clock, duration);

    cout << "������������� ";
    task->show();

    return task;
}

// Task* TaskGen::generateTask(unsigned inputTime) {
//     unsigned clock = inputTime, duration{}, priority{};

//     string name = "������ �" + std::to_string(inputTime);
//     cout << name << endl;

//     cout << "������� ��������� ������ [1-2]" << endl;
//     cin >> priority;
//     while (cin.fail() || priority < 1 || priority > 2) {
//         cin.clear();
//         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//         cout << "�������!" << endl;
//         cout << "������� ��������� ������ [1-2]" << endl;
//         cin >> priority;
//     }
//     cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//     cout << "������� ����������������� ������" << endl;
//     cin >> duration;
//     while (cin.fail() || duration < 1 || duration > 9) {
//         cin.clear();
//         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//         cout << "�������!" << endl;
//         cout << "������� ����������������� ������" << endl;
//         cin >> duration;
//     }
//     cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//     Task* task = new Task(name, priority, clock, duration);
//     return task;
// }