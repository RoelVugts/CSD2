#pragma once

#include "oscillator.h"
#include "sine.h"
#include "square.h"
#include "sawtooth.h"
#include "antiAliasedOsc.h"
#include "antiAliasedSquare.h"
#include "antiAliasedSaw.h"

//This header file contains the base class of the synthesizer

class Synth {
    public:
        Synth();
        Synth(float frequency, float ampltitude);
        Synth(int note, float amplitude);
        ~Synth();

        virtual float getSample() = 0;
        virtual void tick() = 0;
        virtual void setPitch(int note);
        float mtof(int midiNote); //convert midi to frequency

    protected:
        float frequency;
        float amplitude;
        float sample;


};