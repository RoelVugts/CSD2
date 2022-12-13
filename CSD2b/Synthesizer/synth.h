#pragma once

#include "oscillator.h"
#include "sine.h"
#include "square.h"

class Synth {
    public:
        Synth();
        Synth(float frequency, float ampltitude);
        ~Synth();

        virtual float getSample() = 0;
        virtual void setPitch(int pitch) = 0;
        float mtof(int midiNote);

    protected:
        float frequency;
        float amplitude;
        float sample;
};