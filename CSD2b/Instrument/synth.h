#pragma once

#include <iostream>

#include "instrument.h"

using namespace std;

class Synth : public Instrument {
    public:
        Synth();
        Synth(float attackTime, float decayTime, float sustainLevel, float releaseTime, string oscillator, float frerq, float amp, float phase);


        void setOscillator(string oscillator);
        string getOscillator();

        void setFreq(float freq);
        float getFreq();

        void setAmp(float amp);
        float getAmp();

        void setPhase(float phase);
        float getPhase();

        float play(float i);

    private:
        string oscillator;
        float freq;
        float amp;
        float phase;
};