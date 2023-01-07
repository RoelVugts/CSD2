#pragma once

#include "oscillator.h"
#include "sine.h"
#include "square.h"
#include "sawtooth.h"
#include "env.h"
#include "filter.h"

//This header file contains the base class of the synthesizer
class Synth {
    public:
        Synth();
        Synth(float frequency, float ampltitude);
        Synth(int note, float amplitude);
        ~Synth();

        void setAmplitude(float amplitude);
        float getAmplitude();
        float getSynthSample();
        virtual float getSample() = 0;
        virtual void tick() = 0;
        virtual void setPitch(int note);
        virtual void calculatePitch() = 0;
        float mtof(int midiNote); 
        void setLFO(int waveform, float freqLFO, float depthLFO);
        void setEnv(float attack, float decay, float sustain, float release);
        void setFilter(int filterMode, float cutoff);

    protected:
        float frequency;
        float amplitude;
        float sample;
        bool activeLFO = false; //defaults to false so LFO is only active when set
        bool activeEnv = false; ///defaults to false so Env is only active when set
        bool activeFilter = false;
        Oscillator* LFO;
        Oscillator* LFOwave[3] = {new Sine, new Square, new Sawtooth};
        Envelope env = Envelope();
        Filter filter;
        int filterMode;
};