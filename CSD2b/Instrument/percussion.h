#pragma once

#include <iostream>

#include "instrument.h"

using namespace std;

class Percussion : public Instrument {
    public:

    Percussion();
    Percussion(float attackTime, float decayTime, float sustainLevel, float releaseTime, string type);

    void setType(string type);
    void showProperties();

    private:
        string type;
};