#pragma once

#include "oscillator.h"

class Sawtooth : public Oscillator {
    public:
        Sawtooth();
        Sawtooth(float frequency, float amplitude);
        ~Sawtooth();
    
    void calculate();
};