#pragma once

#include "oscillator.h"
#include "sine.h"

class Square : public Oscillator {
    public:
        Square();
        Square(float frequency, float amplitude, float phase, float samplerate);
        Square(float frequency, float amplitude);
        ~Square();
    
    void calculate();

    std::vector<Sine> partials;
};