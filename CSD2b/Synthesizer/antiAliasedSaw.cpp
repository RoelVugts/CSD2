#include "antiAliasedSaw.h"

#include <iostream>
#include <vector>
#include <numeric>

void AntiAliasedSaw::createPartials()
{   
    // partials.clear();
    // partialSamples.clear();
    numHarmonics = (samplerate/2) / frequency; //calculate amount of harmonics till nyquist
    for(int i = 1; i <= numHarmonics; i++)
    {
        partials.push_back(Sine(frequency*i, amplitude/i)); //Saw has all harmonics and amplitude gradually decreases with every harmonic
        partialSamples.push_back(0); //Initialize sample values to 0
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
        partials[i].tick(); //Increment phase of all sine waves and calculate sample value
        partialSamples[i] = partials[i].getSample(); //get the sample value and store in seperate vector
    }

    sample = std::accumulate(partialSamples.begin(), partialSamples.end(), 0.0f); //sum all sample values
}

void AntiAliasedSaw::calculatePartials() //function to recalculate partials freq and amp when pitch has changed
{
        for(float i = 0.0f; i < int(partials.size()); i += 1.0f)
    {
        partials[i].setFrequency(frequency*(i+1.0f));
        partials[i].setAmplitude(amplitude/(i+1.0f));
    }
}


