#include "superSynth.h"

#include <iostream>

SuperSynth::SuperSynth() : Synth(500, 0.5)
{
    std::cout << "Supersynth constructor" << std::endl;
    voices = 5;
    detune = 0.5;

}

SuperSynth::~SuperSynth()
{
    std::cout << "Supersynth destructor" << std::endl;
}

void SuperSynth::calculate()
{
    phase2 += (frequency * 1.02) / samplerate;
    phase3 += (frequency * 0.98) / samplerate;
    phase4 += (frequency * 1.04) / samplerate;
    phase5 += (frequency * 0.96) / samplerate;
    


    sample =    ((amplitude/voices) * phase * 2 - 1) +
                ((amplitude/voices) * phase2 * 2 -1) +
                ((amplitude/voices) * phase3 * 2 -1) +
                ((amplitude/voices) * phase4 * 2 -1) +
                ((amplitude/voices) * phase5 * 2 -1); 
}