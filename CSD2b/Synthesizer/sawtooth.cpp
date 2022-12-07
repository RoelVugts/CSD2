#include "sawtooth.h"

Sawtooth::Sawtooth() : Oscillator()
{

}

Sawtooth::Sawtooth(float frequency, float amplitude) : Oscillator(frequency, amplitude)
{
    phase = 0;
    samplerate = 48000;
}

Sawtooth::~Sawtooth()
{

}

void Sawtooth::calculate()
{
    sample = amplitude*2 * phase - amplitude;
}
