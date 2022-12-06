#include "synth.h"

#include <iostream>

Synth::Synth() : Synth(440, 0.5, 48000)
{
    std::cout << "Concstructed default oscillator" << std::endl;
}

Synth::Synth(float frequency, float amplitude, float samplerate)
:   frequency(frequency), amplitude(amplitude), samplerate(samplerate)
{
    std::cout << "Constructed oscillator: \nFrequency: " << frequency << "\nAmplitude: " << amplitude << std::endl;
}

Synth::Synth(float frequency, float amplitude) : frequency(frequency), amplitude(amplitude)
{
    samplerate = 48000;
}

Synth::~Synth()
{
    std::cout << "Synth destructor" << std::endl;
}

float Synth::getSampleRate()
{
    return samplerate;
}

void Synth::setFrequency(float frequency)
{
    this->frequency = frequency;
}

float Synth::getFrequency()
{
    return frequency;
}

void Synth::setSamplerate(float samplerate) 
{
    this->samplerate = samplerate;
}
