#include "synth.h"

#include <iostream>

Synth::Synth()
{
    std::cout << "Constructed default synth" << std::endl;
}

Synth::Synth(float frequency, float amplitude) : frequency(frequency), amplitude(amplitude)
{
    
}

Synth::~Synth()
{
    std::cout << "Synth destructor" << std::endl;
}

float Synth::mtof(int midiNote) //converts midi to frequency
{
    float freq;
    freq = 440.0f * pow(2.0f, (midiNote - 57.0f)/12.0f);\
    return freq;
}

void Synth::setPitch(int pitch)
{
    this->frequency = mtof(pitch);
}