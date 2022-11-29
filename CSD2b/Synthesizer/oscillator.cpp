#include "oscillator.h"

#include <iostream>

Oscillator::Oscillator() : Oscillator(440, 0.5, 0, 48000)
{
    std::cout << "Concstructed default oscillator" << std::endl;
}

Oscillator::Oscillator(float frequency, float amplitude, float phase, float samplerate)
:   frequency(frequency), amplitude(amplitude), phase(phase), samplerate(samplerate)
{
    std::cout << "Constructed oscillator: \nFrequency: " << frequency << "\nAmplitude: " << amplitude << std::endl;
}

Oscillator::Oscillator(float frequency, float amplitude) : frequency(frequency), amplitude(amplitude)
{
    phase = 0;
    samplerate = 48000;

}

Oscillator::~Oscillator()
{
    std::cout << "Oscillator destructor" << std::endl;
}

void Oscillator::setSamplerate(float samplerate) 
{
    this->samplerate = samplerate;
}

float Oscillator::getSample()
{
    return sample;
}

void Oscillator::setFrequency(float frequency)
{
    this->frequency = frequency;
}

float Oscillator::getFrequency()
{
    return frequency;
}

