#include "antiAliasedOsc.h"

#include <iostream>

AntiAliasedOsc::AntiAliasedOsc() : Oscillator()
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