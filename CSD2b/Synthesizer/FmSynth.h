#pragma once

#include "synth.h"

class FmSynth : public Synth {
    public:
        FmSynth();
        FmSynth(float frequency, float amplitude, int waveform, float modRatio, float modAmount);
        FmSynth(int note, float amplitude, int waveform, float modFrequency, float modAmount);
        ~FmSynth();
    
    void tick();
    float getSample();
    void calculatePitch();


    protected:
        Sine carrier = Sine(frequency, amplitude);
        Oscillator* modulator;
        float modRatio;
        float modAmount;
        Oscillator* waveforms[3] = {new Sine, new Square, new Sawtooth};
};