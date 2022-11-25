#pragma once

#include <iostream>

#include "instrument.h"

using namespace std;

class Percussion : public Instrument {
    public:

    Percussion();
    Percussion(float attackTime, float decayTime, float sustainLevel, float releaseTime, string type);


    void showProperties();

    void setType(string type);
    string getType();

    void setResonance(int resonance);
    int getResonance();

    protected:
        string type;
        int resonance;
};

