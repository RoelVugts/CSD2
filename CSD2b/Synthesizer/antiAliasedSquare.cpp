#include "antiAliasedSquare.h"

#include <iostream>
#include <vector>
#include <numeric>

AntiAliasedSquare::AntiAliasedSquare() : AntiAliasedOsc()
{
    std::cout << " Anti Aliased Square constructor" << std::endl;
    numHarmonics = ((samplerate/2) / frequency);
    for(int i = 1; i <= numHarmonics; i += 2)
    {
        partials.push_back(Sine(frequency*i, amplitude/i));
        partialSamples.push_back(0);
    }
}

AntiAliasedSquare::~AntiAliasedSquare()
{
    std::cout << " Anti Aliased Square constructor" << std::endl;
}

void AntiAliasedSquare::calculate()
{
    for(int i = 0; i < int(partials.size()); i++)
    {
        partials[i].tick(); //calculate sine sample values
        partialSamples[i] = partials[i].getSample();
    }
    sample = std::accumulate(partialSamples.begin(), partialSamples.end(), 0.0f); //add all sample values
}