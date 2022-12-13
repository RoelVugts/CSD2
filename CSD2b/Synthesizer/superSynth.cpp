#include "superSynth.h"

#include <iostream>
#include <vector>
#include <numeric>

SuperSynth::SuperSynth() : Synth(400, 1.0)
{
    std::cout << "Supersynth constructor" << std::endl;
}

SuperSynth::SuperSynth(float frequency, float amplitude, int numVoices, int detunePercentage) 
: Synth(frequency, amplitude), numVoices(numVoices), detunePercentage(detunePercentage)
{
    std::cout << "Supersynth constructor" << std::endl;

    if (numVoices != 1) { 
        detuneDepth = (0.1 * (detunePercentage/100.0f)) / (numVoices-1); //Scale 0.1 (max detune) based on detunePercentage
    } else {
        detuneDepth = 0.0f; //if only 1 voice than there can't be detune so depth = 0
    }

    float detuneValue;

    for(int i = 0; i < numVoices; i++) 
    {   
        // std::cout << "DetuneDepth: " << detuneDepth << std::endl;
        detuneValue = (1.0f - detuneDepth*int((numVoices/2)) + detuneDepth * i);
        // std::cout << "Detune Value: " << detuneValue << std::endl;
        squares.push_back(AntiAliasedSquare((frequency/2)*detuneValue, amplitude));
        saws.push_back(AntiAliasedSaw(frequency*detuneValue, amplitude));
        voiceSamples.push_back(0);
        voiceSamples.push_back(0); //create numVoices * 2 amount of empty sample elements
        // saws[i].setAmplitude(0.0f);  
        // squares[i].setAmplitude(amplitude/2.0f);
    }
}

SuperSynth::~SuperSynth()
{
    std::cout << "Supersynth destructor" << std::endl;
}

void SuperSynth::tick()
{
    // std::cout << "Voice amount: " << int(squares.size());
    for(int i = 0; i < numVoices; i++) 
    {
        squares[i].tick();
        saws[i].tick();
    }
}

float SuperSynth::getSample()
{
    for(int i = 0; i < numVoices; i++)
    {
        voiceSamples[i] = squares[i].getSample();
        voiceSamples[i+numVoices] = saws[i].getSample();
    }
    sample = std::accumulate(voiceSamples.begin(), voiceSamples.end(), 0.0f);
    sample /= numVoices*2;
    return sample;
}

void SuperSynth::setPitch(int pitch)
{
    float detuneValue;
    frequency = mtof(pitch);
    // std::cout << "DetuneDepth: " << detuneDepth << std::endl;
    for(int i = 0; i < numVoices; i++)
    {
        detuneValue = (1.0f - detuneDepth*int((numVoices/2)) + detuneDepth * i);
        // std::cout << "Detune Value: " << detuneValue << std::endl;
        squares[i].setFrequency(frequency*detuneValue);
        saws[i].setFrequency(frequency*detuneValue);
    }
}