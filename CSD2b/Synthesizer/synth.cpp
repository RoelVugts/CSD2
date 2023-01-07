#include "synth.h"

#include <iostream>

Synth::Synth()
{
    // std::cout << "Constructed default synth" << std::endl;
}

Synth::Synth(float frequency, float amplitude) : frequency(frequency), amplitude(amplitude)
{
    
}

Synth::Synth(int note, float amplitude)
{
    frequency = mtof(note);
    this->amplitude = amplitude;
    // std::cout << "Amp synth constr" << amplitude << std::endl;
}

Synth::~Synth()
{
    // std::cout << "Synth destructor" << std::endl;
}

float Synth::mtof(int midiNote) //converts midi to frequency
{
    float freq;
    freq = 440.0f * pow(2.0f, (midiNote - 69.0f)/12.0f); //convert midi to Freq
    return freq;
}

//fucction that changes the pitch when melody gives it a new note
void Synth::setPitch(int note)
{
    this->frequency = mtof(note);
    calculatePitch();
    
    //trigger envelope when new note is received
    if (activeEnv) 
    {
        env.trigger();
    }
}

void Synth::setLFO(int waveform, float freqLFO, float depthLFO)
{
    LFO = LFOwave[waveform];

    LFO->setFrequency(freqLFO);
    LFO->setAmplitude(depthLFO);
    activeLFO = true;
}

void Synth::setEnv(float attack, float decay, float sustain, float release)
{
    env.setADSR(attack, decay, sustain, release);
    activeEnv = true;
}

void Synth::setAmplitude(float amplitude)
{
    this->amplitude = amplitude;
}

float Synth::getAmplitude()
{
    return amplitude;
}

void Synth::setFilter(int filterMode, float cutoff)
{
    this->filterMode = filterMode;
    filter.setCutoff(cutoff);
    activeFilter = true;
    std::cout << "Cutoff: " << cutoff << std::endl;
}


float Synth::getSynthSample()
{
    if (activeFilter)
    {
        switch(filterMode) {
            case 0:
            return filter.lowpass(getSample());
            break;
            case 1:
            return filter.highpass(getSample());
            break;
        }
    } else 
    {
        return getSample();
    }

}