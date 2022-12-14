#include "FmSynth.h"

FmSynth::FmSynth() : FmSynth(100, 1.0, 0, 10, 1.0)
{

}

FmSynth::FmSynth(float frequency, float amplitude, int waveform, float modFrequency, float modAmount)
: Synth(frequency, amplitude)
{
    // if (waveform == "Sine" || "sine") {
    //     modulator = waveforms[0];
    // } else if (waveform == "Square" || "square") {
    //     modulator = waveforms[1];
    // } else if (waveform == "Saw" || "saw") {
    //     modulator = waveforms[2];
    // }

    modulator = waveforms[waveform];

    this->modFrequency = modFrequency;
    this->modAmount = modAmount;

    modulator->setFrequency(modFrequency);
    modulator->setAmplitude(modAmount);
}

FmSynth::FmSynth(int note, float amplitude, int waveform, float modFrequency, float modAmount)
: FmSynth(mtof(note), amplitude, waveform, modFrequency, modAmount)
{

}

FmSynth::~FmSynth()
{

}

void FmSynth::tick()
{
    if (activeLFO) {
        modulator->setAmplitude(modAmount*(LFO->getSample()+1)); //Modulate the FM amount with the LFO
        LFO->tick();
    }
    
    carrier.setFrequency(frequency*(modulator->getSample()+1)); //modulate frequency of carrier with modulator
    carrier.tick();
    modulator->tick();

}

float FmSynth::getSample()
{
    sample = carrier.getSample();
    return sample;
}

void FmSynth::setLFO(std::string waveform, float freqLFO, float depthLFO)
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