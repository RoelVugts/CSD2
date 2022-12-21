#include "antiAliasedSquare.h"

#include <iostream>
#include <vector>
#include <numeric>

void AntiAliasedSquare::createPartials()
{
    numHarmonics = ((samplerate/2) / frequency); // 20 is the lowest frequency we can play
    for(int i = 1; i <= numHarmonics; i += 2) //i += 2 to only create uneven harmonics
    {   
        partials.push_back(Sine(frequency*i, amplitude/i)); //amplitude gradually decreases with higher harmonic
        partialSamples.push_back(0); //initialize sample value to 0
    }
}

AntiAliasedSquare::AntiAliasedSquare() : AntiAliasedOsc()
{
    // std::cout << " Anti Aliased Square constructor" << std::endl;
    createPartials();
}

AntiAliasedSquare::AntiAliasedSquare(float frequency, float amplitude) 
: AntiAliasedOsc(frequency, amplitude)
{
    // std::cout << " Anti Aliased Square constructor" << std::endl;
    createPartials();
}


AntiAliasedSquare::~AntiAliasedSquare()
{
    // std::cout << " Anti Aliased Square constructor" << std::endl;
}

void AntiAliasedSquare::calculate()
{
    for(int i = 0; i < int(partials.size()); i++)
    {
        if (partials[i].getFrequency() < samplerate/2) {
        partials[i].tick(); //calculate sine sample values
        partialSamples[i] = partials[i].getSample(); //push sample values in vector
        }
    }
    sample = std::accumulate(partialSamples.begin(), partialSamples.end(), 0.0f); //add all sample values
}

//function to recaluclate partials freq and amp when pitch has changed
void AntiAliasedSquare::calculatePartials() 
{

    numHarmonics = ((samplerate/2) / frequency) / 2; //calculate amount of uneven harmonics till nyquist

    int partialDelta = numHarmonics - int(partials.size()); //calculate excess/shortage of partials

    if (partialDelta > 0) 
    {
        for (int i = 1; i <= partialDelta; i += 2) 
        {
            partials.push_back(Sine(frequency*i, amplitude/i)); //add partials if below nyquist
            partialSamples.push_back(0);
        }
    } else if (partialDelta < 0) 
    {
        for (int i = 0; i < partialDelta; i ++) 
        {
            partials.pop_back();
        }
    }
    
    //update pitch for all partials
        for(float i = 0.0f; i < int(partials.size()); i += 1.0f)
    {
        partials[i].setFrequency(frequency*(i*2.0f+1.0f));
        if (partials[i].getFrequency() < samplerate/2) 
        {
            partials[i].setAmplitude(amplitude/(i*2.0f+1.0f));
        } else {
            partials[i].setAmplitude(0.0f); //all partials above nyquist are 0 (just in case)
        }

    }
}