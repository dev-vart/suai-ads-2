#include "task.h"

void Task::setName(const string& name) { this->name = name; }

void Task::setPriority(unsigned priority) { this->priority = priority; }

void Task::setClock(unsigned clock) { this->clock = clock; }

void Task::setDuration(unsigned duration) { this->duration = duration; }

const string& Task::getName() const { return name; }

unsigned Task::getPriority() const { return priority; }

unsigned Task::getClock() const { return clock; }

unsigned Task::getDuration() const { return duration; }

Task::Task(string name, unsigned priority, unsigned clock, unsigned duration) {
    this->name = name;
    this->duration = duration;
    this->clock = clock;
    this->priority = priority;
}

void Task::show() const {
    cout << name << ": приоритет " << priority << ", такт " << clock << ",  время выполнения " << duration << endl;
}