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
        partials.push_back(Sine(frequency*i, amplitude/i)); //amplitude gradually decreases with higher harmonic
        partialSamples.push_back(0); //initialize sample value to 0
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
        if (partials[i].getFrequency() < samplerate/2) {
        partials[i].tick(); //calculate sine sample values
        partialSamples[i] = partials[i].getSample(); //push sample values in vector
        }
    }

    sample = std::accumulate(partialSamples.begin(), partialSamples.end(), 0.0f); //sum all sample values
}

//function to recalculate partials freq and amp when pitch has changed
void AntiAliasedSaw::calculatePartials() 
{

    numHarmonics = (samplerate/2) / frequency; //calculate amount of harmonics till nyquist

    for (int i =  0 ; i < int(partials.size()); i++) {
        if (partials[i].getFrequency() > samplerate/2) 
        {
        partials.erase(partials.begin()+i); //delete partials above nyquist
        partialSamples.erase(partialSamples.begin()+i);
        }
    }

    if (int(partials.size()) < numHarmonics) {
        for (int i = 1; i <= (numHarmonics - int(partials.size())); i++) {
            partials.push_back(Sine(frequency*i, amplitude/i)); //add partials if below nyquist
            partialSamples.push_back(0);
        }
    }

    for(float i = 0.0f; i < int(partials.size()); i += 1.0f)
    {
        
        partials[i].setFrequency(frequency*(i+1.0f));

        if (partials[i].getFrequency() < samplerate/2) {
            partials[i].setAmplitude(amplitude/(i+1.0f));
        } else {
            partials[i].setAmplitude(0.0f); //all partials above nyquist have amp 0
        }
        
    }



}


