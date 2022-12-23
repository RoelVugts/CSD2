#pragma once
#include <vector>

#include "synth.h"
#include "oscillator.h"
#include "square.h"
#include "sawtooth.h"
#include "antiAliasedSquare.h"
#include "antiAliasedSaw.h"

class SuperSynth : public Synth {
    public:
        SuperSynth();
        SuperSynth(float frequency, float amplitude, int numVoices, int detunePercentage, bool antiAliasing);
        SuperSynth(int note, float amplitude, int numVoices, int detunePercentage, bool antiAliasing);
        ~SuperSynth();

        void tick();
        float getSample();
        void calculatePitch();
        int numVoices;
        int detunePercentage;
        float detuneDepth;
        bool antiAliasing;
    
    protected:
        std::vector<Oscillator*> squares;
        std::vector<Oscillator*> saws; 
        std::vector<float> voiceSamples;
};