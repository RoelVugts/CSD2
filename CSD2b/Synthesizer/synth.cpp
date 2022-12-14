#include "synth.h"

#include <iostream>

Synth::Synth()
{
    std::cout << "Constructed default synth" << std::endl;
}

Synth::Synth(float frequency, float amplitude) : frequency(frequency), amplitude(amplitude)
{
    
}

Synth::Synth(int note, float amplitude)
{
    frequency = mtof(note);
    this->amplitude = amplitude;
}

Synth::~Synth()
{
    std::cout << "Synth destructor" << std::endl;
}

float Synth::mtof(int midiNote) //converts midi to frequency
{
    float freq;
    freq = 440.0f * pow(2.0f, (midiNote - 69.0f)/12.0f); //convert midi to Freq
    return freq;
}

void Synth::setPitch(int note)
{
    this->frequency = mtof(note);
}

void Synth::setLFO(std::string waveform, float freqLFO, float depthLFO)
{
    if (waveform == "Sine" || "sine") {
        LFO = LFOwave[0];
    } else if (waveform == "Square" || "square") {
        LFO = LFOwave[1];
    } else if (waveform == "Saw" || "saw") {
        LFO = LFOwave[2];
    }

    LFO->setFrequency(freqLFO);
    LFO->setAmplitude(depthLFO);
    activeLFO = true;
}