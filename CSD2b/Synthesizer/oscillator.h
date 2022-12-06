#pragma once

#include <cmath>
#include <vector>

#include "synth.h"


#define SAMPLERATE 48000

class Oscillator : public Synth {
    public:
        Oscillator();
        Oscillator(float frequency, float amplitude, float samplerate, float phase);
        Oscillator(float frequency, float amplitude);
        ~Oscillator();

        float getSample();
        void tick();

    protected:
        float phase;
        float sample;
        float samplerate = SAMPLERATE;
        double pi = acos(-1);

        virtual void calculate() = 0;
};