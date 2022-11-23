#pragma once

#include <iostream>

#include "instrument.h"
#include "synth.h"

using namespace std;

class Granular : public Synth {
    public:
        Granular(); //default constructor
        Granular(float attackTime, float decayTime, float sustainLevel, float releaseTime, string oscillator, float freq, float amp, float phase, int grainSize, int density, float playbackSpeed); //constructor
        ~Granular(); //destructor

    protected:
        int grainSize;
        int density;
        float playbackSpeed;

};