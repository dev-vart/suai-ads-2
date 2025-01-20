#pragma once

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

class Task {
    string name;
    unsigned priority;
    unsigned clock;
    unsigned duration;

   public:
    void setName(const string& name);
    void setPriority(unsigned priority);
    void setClock(unsigned clock);
    void setDuration(unsigned duration);
    const string& getName() const;
    unsigned getPriority() const;
    unsigned getClock() const;
    unsigned getDuration() const;
    explicit Task(string name = "", unsigned priority = 0, unsigned clock = 0, unsigned duration = 0);
    void show() const;
};
