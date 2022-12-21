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
        std::vector<Oscillator*> squares; //Oscillator ptr so user can choose oscillators with or without aliasing
        std::vector<Oscillator*> saws; //Oscillator ptr so user can choose oscillators with or without aliasing
        std::vector<float> voiceSamples;
};