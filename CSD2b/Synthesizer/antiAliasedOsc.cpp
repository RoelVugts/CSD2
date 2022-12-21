#include "antiAliasedOsc.h"

#include <iostream>

AntiAliasedOsc::AntiAliasedOsc() : Oscillator()
{
    // std::cout << "Anti Aliased Oscillator constructor" << std::endl;

}

AntiAliasedOsc::AntiAliasedOsc(float frequency, float amplitude) : Oscillator(frequency, amplitude)
{
    // std::cout << "Anti Aliased Oscillator constructor" << std::endl;
}

AntiAliasedOsc::~AntiAliasedOsc()
{
    // std::cout << "Anti Aliased Oscillator destructor" << std::endl;
}

void AntiAliasedOsc::tick()
{
    calculate(); //calculate sample value in sub class
}

void AntiAliasedOsc::setFrequency(float frequency)
{
    this->frequency = frequency;
    calculatePartials(); //recalculate amp & freq for each partial
}

void AntiAliasedOsc::setAmplitude(float amplitude)
{
    this->amplitude = amplitude;
    calculatePartials(); //recalculate amp & freq for each partial
}