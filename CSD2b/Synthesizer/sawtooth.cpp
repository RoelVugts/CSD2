#include "sawtooth.h"

Sawtooth::Sawtooth() : Oscillator(500, 1.0, 0, 48000)
{

}

Sawtooth::Sawtooth(float frequency, float amplitude, float phase, float samplerate) : Oscillator(frequency, amplitude, phase, samplerate)
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

float Sawtooth::process()
{
    phase += frequency / samplerate;
    if(phase > 1.0f)
    {
        phase -= 1.0f;
    }

    sample = amplitude * phase;
    return sample;
}