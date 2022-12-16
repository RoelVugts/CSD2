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
        SuperSynth(float frequency, float amplitude, int numVoices, int detunePercentage);
        SuperSynth(int note, float amplitude, int numVoices, int detunePercentage);
        ~SuperSynth();

        void tick();
        float getSample();
        void calculatePitch();
        int numVoices;
        int detunePercentage;
        float detuneDepth;
    
    protected:
        std::vector<AntiAliasedSquare> squares;
        std::vector<AntiAliasedSaw> saws;
        std::vector<float> voiceSamples;

};