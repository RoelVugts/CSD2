#pragma once
#include <vector>

#include "synth.h"
#include "oscillator.h"
#include "square.h"
#include "sawtooth.h"

class SuperSynth : public Synth {
    public:
        SuperSynth();
        SuperSynth(float frequency, float amplitude, int numVoices, int detunePercentage);
        SuperSynth(int note, float amplitude, int numVoices, int detunePercentage);
        ~SuperSynth();

        void tick();
        float getSample();
        void calculatePitch();
        int numVoices;
        int detunePercentage;
        float detuneDepth;
        bool antiAliasing;
        float detuneValue[6]; //array for storing detuneValue per voice
    
    protected:
        std::vector<Oscillator*> squares;
        std::vector<Oscillator*> saws; 
        std::vector<float> voiceSamples;
};