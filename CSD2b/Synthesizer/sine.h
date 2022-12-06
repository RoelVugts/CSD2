#ifndef _SINE_H_
#define _SINE_H_
#include <iostream>
#include <cmath>
#include "oscillator.h"


class Sine : public Oscillator
{
  public:
    //Constructor and destructor
    Sine();
    Sine(float frequency, float amplitude);
    ~Sine();

    void calculate();
};

#endif
