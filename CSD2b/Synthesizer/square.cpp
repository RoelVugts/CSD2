#include "square.h"

#include <cmath>
#include <vector>
#include <numeric>

Square::Square() : Oscillator(1000, 1.0)
{

}

Square::Square(float frequency, float amplitude) : Oscillator(frequency, amplitude)
{
    phase = 0;
    samplerate = 48000;
}

Square::~Square()
{

}

void Square::calculate()
{
    if(phase < 0.5)
    {
        sample = amplitude;
    } else {
        sample = amplitude*-1.0f;
    }
}