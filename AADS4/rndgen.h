#pragma once

#include <ctime>
#include <random>

class RandomGen {
   public:
    RandomGen() { rndgen.seed(static_cast<unsigned int>(std::time(nullptr))); }

    int rnd(int lower_border, int upper_border) {
        std::uniform_int_distribution<int> dist(lower_border, upper_border);
        return dist(rndgen);
    }

   private:
    std::mt19937 rndgen;
};
