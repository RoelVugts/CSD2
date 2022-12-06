#include "synth.h"

#include <iostream>

Synth::Synth()
{
    std::cout << "Constructed default synth" << std::endl;
}

Synth::~Synth()
{
    std::cout << "Synth destructor" << std::endl;
}