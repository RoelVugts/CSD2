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