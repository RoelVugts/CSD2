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
    samplerate = 48000; //default samplerate
    phaseDelta = frequency / samplerate;
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

float Oscillator::getAmplitude()
{
    return amplitude;
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

//increment phase of oscillator
void Oscillator::tick()
{
    phase += frequency / samplerate;
    if(phase > 1.0f){
        phase -= 1.0f;
    }
    calculate(); //call calculate() from subclass
}

//Anti-aliasing method that smoothes steep edges in the waveform
float Oscillator::polyBLEP(float t)
{
    float dt = phaseDelta;
    if (t < dt) 
    {
        t /= dt;
        return t+t - t*t - 1.0;
    }
    else if (t > 1.0 - dt) 
    {
        t = (t - 1.0) / dt;
        return t*t + t+t + 1.0;
    }
    else return 0.0;

}