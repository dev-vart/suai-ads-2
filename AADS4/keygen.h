#pragma once

#include <iostream>

using std::string;

#include "rndgen.h"

class KeyGen {
    RandomGen randomGen;

   public:
    KeyGen() : randomGen() {}
    string generateKey() {
        string key = "A111AA";

        for (int i = 0; i < 6; i++) {
            int num = randomGen.rnd(48, 57);
            int letter = randomGen.rnd(65, 90);

            if (key[i] == '1')
                key[i] = num;
            else
                key[i] = letter;
        }

        return key;
    }
};
