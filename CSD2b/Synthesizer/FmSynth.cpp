#include "FmSynth.h"

FmSynth::FmSynth() : FmSynth(100, 1.0)
{

}

FmSynth::FmSynth(float frequency, float amplitude)
: Synth(frequency, amplitude)
{
 this->modulator = waveforms[0];
}

FmSynth::~FmSynth()
{

}

void FmSynth::tick()
{
    modulator->setFrequency(10);
    modulator->setAmplitude(1.0);
    carrier.setFrequency(frequency*(modulator->getSample()+1)); //modulate frequency of carrier with modulator
    carrier.tick();
    modulator->tick();
}

float FmSynth::getSample()
{
    sample = carrier.getSample();
    return sample;
}