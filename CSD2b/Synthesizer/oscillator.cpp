#include "oscillator.h"


#include <iostream>

Oscillator::Oscillator() : Synth(440, 0.5, 48000)
{
    std::cout << "Concstructed default oscillator" << std::endl;
    phase = 0;
}

Oscillator::Oscillator(float frequency, float amplitude, float samplerate, float phase)
:   Synth(frequency, amplitude, samplerate) , phase(phase)
{
    std::cout << "Constructed oscillator: \nFrequency: " << frequency << "\nAmplitude: " << amplitude << std::endl;
}

Oscillator::Oscillator(float frequency, float amplitude) : Synth(frequency, amplitude)
{
    phase = 0;
    samplerate = 48000;

}

Oscillator::~Oscillator()
{
    std::cout << "Oscillator destructor" << std::endl;
}


float Oscillator::getSample()
{
    return sample;
}

void Oscillator::tick()
{
    phase += frequency / samplerate;
    if(phase > 1.0f){
        phase -= 1.0f;
    }
    calculate();
}

