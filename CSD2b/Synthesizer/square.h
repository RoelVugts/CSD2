#pragma once

#include "oscillator.h"

class Square : public Oscillator {
    public:
        Square();
        Square(float frequency, float amplitude);
        ~Square();
    
    void calculate();

};