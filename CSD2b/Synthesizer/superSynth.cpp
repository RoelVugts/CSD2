#include "superSynth.h"

#include <iostream>
#include <vector>
#include <numeric>

SuperSynth::SuperSynth() : Synth(400, 1.0)
{
    // std::cout << "Supersynth constructor" << std::endl;
}



SuperSynth::SuperSynth(float frequency, float amplitude, int numVoices, int detunePercentage) 
: Synth(frequency, amplitude), numVoices(numVoices), detunePercentage(detunePercentage)
{
    // std::cout << "Supersynth constructor" << std::endl;

    if (numVoices != 1) { 
        detuneDepth = (0.1 * (detunePercentage/100.0f)) / (numVoices-1); //Scale 0.1 (max detune) based on detunePercentage
    } else {
        detuneDepth = 0.0f; //if there is only 1 voice than there can't be detune so depth = 0
    }

    for(int i = 0; i < numVoices; i++) 
    {   
        detuneValue[i] = (1.0f - detuneDepth*int((numVoices/2)) + detuneDepth * i); //calculate detune value per voice
        squares.push_back(Square((frequency/2)*detuneValue[i], amplitude));
        saws.push_back(Sawtooth(frequency*detuneValue[i], amplitude));
        

        voiceSamples.push_back(0);
        voiceSamples.push_back(0); //create numVoices * 2 amount of empty sample elements
    }
}

SuperSynth::SuperSynth(int note, float amplitude, int numVoices, int detunePercentage) 
: SuperSynth(mtof(note), amplitude, numVoices, detunePercentage)
{

}

SuperSynth::~SuperSynth()
{
    // std::cout << "Supersynth destructor" << std::endl;
}

void SuperSynth::tick() 
{
    for(int i = 0; i < numVoices; i++) 
    {
        if (activeLFO) {
            squares[i].setFrequency(frequency*(LFO->getSample()+1)*detuneValue[i]); //Modulate pitch with LFO
            saws[i].setFrequency(frequency*(LFO->getSample()+1)*detuneValue[i]); //Modulate pitch with LFO
            LFO->tick();
        }
        if (activeEnv) {
            squares[i].setAmplitude(amplitude*env.getLevel()); //Modulate amp with Env
            saws[i].setAmplitude(amplitude*env.getLevel()); //Modulate amp with Env
        }

        squares[i].tick(); //Move phase of oscillators 1 step further
        saws[i].tick(); //Move phase of oscillators 1 step further

    }

}

float SuperSynth::getSample()
{
    for(int i = 0; i < numVoices; i++)
    {
        voiceSamples[i] = squares[i].getSample();
        voiceSamples[i+numVoices] = saws[i].getSample(); //push sample values in seperate vector
    }
    sample = std::accumulate(voiceSamples.begin(), voiceSamples.end(), 0.0f); //add all sample values
    sample /= numVoices*2; //divide so the amplitude won't clip
    return sample;


}

void SuperSynth::calculatePitch() //function that recalculates frequency for each voice when pitch is changed
{
    float detuneValue;
    for(int i = 0; i < numVoices; i++)
    {
        detuneValue = (1.0f - detuneDepth*int((numVoices/2)) + detuneDepth * i);
        squares[i].setFrequency(frequency*detuneValue);
        saws[i].setFrequency(frequency*detuneValue);
 
    }
    
}