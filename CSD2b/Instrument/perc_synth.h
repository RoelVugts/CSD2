#pragma once

#include "synth.h"
#include "percussion.h"

using namespace std;

class PercSynth : public Percussion, public Synth {
    public:
        PercSynth();
        PercSynth(float attackTime, float decayTime, float sustainLevel, float releaseTime, string type, string oscillator, float freq, float amp, float phase);
        ~PercSynth();

        void setSound(string sound);

    private:
        string noiseOsc;
};  