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

    float rndreal(int lower_border, int upper_border) {
        std::uniform_int_distribution<int> dist(lower_border * 10, upper_border * 10);
        return static_cast<float>(dist(rndgen)) / 10.0f;
    }

   private:
    std::mt19937 rndgen;
};
