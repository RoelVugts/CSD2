#include "antiAliasedSaw.h"

#include <iostream>
#include <vector>
#include <numeric>

void AntiAliasedSaw::createPartials() //Gok dat hier iets mis gaat bij het spelen van een melodie
{   
    partials.clear();
    partialSamples.clear();
    numHarmonics = (samplerate/2) / frequency;
    for(int i = 1; i <= numHarmonics; i++)
    {
        partials.push_back(Sine(frequency*i, amplitude/i));
        partialSamples.push_back(0);
    }
}

AntiAliasedSaw::AntiAliasedSaw() : AntiAliasedOsc()
{
    std::cout << "Anti Aliased Saw Constructor" << std::endl;
    createPartials();
}

AntiAliasedSaw::AntiAliasedSaw(float frequency, float amplitude)
:   AntiAliasedOsc(frequency, amplitude)
{
    std::cout << "Anti Aliased Saw Constructor" << std::endl;
    createPartials();
}

AntiAliasedSaw::~AntiAliasedSaw()
{
    std::cout << "Anti Aliased Saw Destructor" << std::endl;
}

void AntiAliasedSaw::calculate()
{
    for(int i = 0; i < int(partials.size()); i++)
    {
        partials[i].tick();
        partialSamples[i] = partials[i].getSample();
    }

    sample = std::accumulate(partialSamples.begin(), partialSamples.end(), 0.0f);
}


