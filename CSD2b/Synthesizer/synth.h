#pragma once

#include "oscillator.h"
#include "sine.h"
#include "square.h"

class Synth {
    public:
        Synth();
        Synth(float frequency, float ampltitude);
        ~Synth();

        virtual float getSample() = 0;

    protected:
        float frequency;
        float amplitude;
        float sample;
};