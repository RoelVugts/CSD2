#include "antiAliasedSquare.h"

#include <iostream>
#include <vector>
#include <numeric>

void AntiAliasedSquare::createPartials()
{
    partials.clear();
    partialSamples.clear();
    numHarmonics = ((samplerate/2) / frequency);
    for(int i = 1; i <= numHarmonics; i += 2) //i += 2 to only create uneven harmonics
    {
        partials.push_back(Sine(frequency*i, amplitude/i)); //amplitude gradually decreases with higher harmonic
        partialSamples.push_back(0); //initialize sample value to 0
    }
}

AntiAliasedSquare::AntiAliasedSquare() : AntiAliasedOsc()
{
    std::cout << " Anti Aliased Square constructor" << std::endl;
    createPartials();
}

AntiAliasedSquare::AntiAliasedSquare(float frequency, float amplitude) 
: AntiAliasedOsc(frequency, amplitude)
{
    std::cout << " Anti Aliased Square constructor" << std::endl;
    createPartials();
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
        partialSamples[i] = partials[i].getSample(); //push sample values in vector
    }
    sample = std::accumulate(partialSamples.begin(), partialSamples.end(), 0.0f); //add all sample values
}

void AntiAliasedSquare::calculatePartials() //function to recaluclate partials freq and amp when pitch has changed
{
        for(float i = 0.0f; i < int(partials.size()); i += 1.0f)
    {
        partials[i].setFrequency(frequency*(i*2.0f+1.0f));
        partials[i].setAmplitude(amplitude/(i*2.0f+1.0f));
    }
}