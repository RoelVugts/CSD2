#include "oscillator.h"


#include <iostream>

Oscillator::Oscillator() : Oscillator(500, 1.0)
{
    // std::cout << "Concstructed default oscillator" << std::endl;
}

Oscillator::Oscillator(float frequency, float amplitude) : frequency(frequency), amplitude(amplitude)
{
    phase = 0.0f;
    sample = 0.0f;
    samplerate = 48000;
}

Oscillator::~Oscillator()
{
    // std::cout << "Oscillator destructor" << std::endl;
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

float Oscillator::getSampleRate()
{
    return samplerate;
}

void Oscillator::setSamplerate(float samplerate) 
{
    this->samplerate = samplerate;
}

void Oscillator::setAmplitude(float amplitude)
{
    this->amplitude = amplitude;
}


void Oscillator::tick()
{
    phase += frequency / samplerate;
    if(phase > 1.0f){
        phase -= 1.0f;
    }
    calculate(); //call calculate() from subclass
}