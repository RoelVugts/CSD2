#pragma once

#include <iostream>

#include "instrument.h"

using namespace std;

class Sampler : public Instrument {
    public:
        Sampler();
        Sampler(float attackTime, float decayTime, float sustainLevel, float releaseTime, string sample);
        ~Sampler();


        void setSample(string sample);
        string getSample();

        void setPitch(int pitch);
        int getPitch();

    protected:
        string sample;
        int pitch;

};