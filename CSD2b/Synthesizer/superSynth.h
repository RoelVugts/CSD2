#pragma once

#include "synth.h"
#include "oscillator.h"
#include "square.h"
#include "sawtooth.h"
#include "antiAliasedSquare.h"
#include "antiAliasedSaw.h"

class SuperSynth : public Synth {
    public:
        SuperSynth();
        SuperSynth(float frequency, float amplitude);
        ~SuperSynth();

        virtual void tick();
        float getSample();
    
    protected:
        AntiAliasedSquare square = AntiAliasedSquare();
        AntiAliasedSaw saw = AntiAliasedSaw();

};