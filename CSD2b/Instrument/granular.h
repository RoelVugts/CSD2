#pragma once

#include <iostream>

#include "instrument.h"
#include "sampler.h"

using namespace std;

class Granular : public Sampler {
    public:
        Granular(); //default constructor
        Granular(float attackTime, float decayTime, float sustainLevel, float releaseTime, string sample, int grainSize, int density, float playbackSpeed); //constructor
        ~Granular(); //destructor

    protected:
        int grainSize;
        int density;
        float playbackSpeed;

};