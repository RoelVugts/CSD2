#include "superSynth.h"

#include <iostream>

SuperSynth::SuperSynth() : Synth(400, 1.0)
{
    std::cout << "Supersynth constructor" << std::endl;
    // square.setFrequency(frequency);
    // saw.setFrequency(frequency*2.0f);
    // saw.setAmplitude(0.0f);  
    // square.setAmplitude(0.0f);
}

SuperSynth::SuperSynth(float frequency, float amplitude) : Synth(frequency, amplitude)
{
    std::cout << "Supersynth constructor" << std::endl;
    square.setFrequency(frequency);
    saw.setFrequency(frequency);
}

SuperSynth::~SuperSynth()
{
    std::cout << "Supersynth destructor" << std::endl;
}

void SuperSynth::tick()
{
    square.tick();
    saw.tick();
}

float SuperSynth::getSample()
{
    sample = square.getSample() + saw.getSample();
    return sample;
}

void SuperSynth::setPitch(int pitch)
{
    square.setFrequency(mtof(pitch));
    saw.setFrequency(mtof(pitch));
}