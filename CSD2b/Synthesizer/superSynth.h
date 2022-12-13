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
        ~SuperSynth();

        virtual void tick();
        float getSample();
        void setPitch(int pitch);
        int numVoices = 6;
        int detunePercentage = 50;
        float detuneDepth;
    
    protected:
        std::vector<AntiAliasedSquare> squares;
        std::vector<AntiAliasedSaw> saws;
        std::vector<float> voiceSamples;

};