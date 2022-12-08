#include "antiAliasedOsc.h"

#include <iostream>

AntiAliasedOsc::AntiAliasedOsc() : Oscillator()
{
    std::cout << "Anti Aliased Oscillator constructor" << std::endl;

}

AntiAliasedOsc::AntiAliasedOsc(float frequency, float amplitude) : Oscillator(frequency, amplitude)
{
    std::cout << "Anti Aliased Oscillator constructor" << std::endl;
}

AntiAliasedOsc::~AntiAliasedOsc()
{
    std::cout << "Anti Aliased Oscillator destructor" << std::endl;
}

void AntiAliasedOsc::tick()
{
    calculate();
}

void AntiAliasedOsc::setFrequency(float frequency)
{
    this->frequency = frequency;
    createPartials();
}