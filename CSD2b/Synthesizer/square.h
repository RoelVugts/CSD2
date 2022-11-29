#pragma once

#include "oscillator.h"

class Square : public Oscillator {
    public:
        Square();
        Square(float frequency, float amplitude, float phase, float samplerate);
        Square(float frequency, float amplitude);
        ~Square();
    
    float process();
};