#pragma once

#include "synth.h"
#include "oscillator.h"

class FmSynth : public Synth {
    public:
        FmSynth();
        FmSynth(float frequency, float amplitude);
        ~FmSynth();
    
    void tick();
    float getSample();


    protected:
        Sine carrier = Sine(frequency, amplitude);
        Oscillator* modulator;
        Oscillator* waveforms[3] = {new Sine, new Square, new Sine};
        float modFrequency;
        float modAmount;
};