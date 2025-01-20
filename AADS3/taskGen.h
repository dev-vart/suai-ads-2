#pragma once

#include <iostream>

#include "rndgen.h"
#include "task.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

class TaskGen {
    RandomGen randomGen;

   public:
    TaskGen() : randomGen() {}
    Task* autoGenerateTask(unsigned clock);
};