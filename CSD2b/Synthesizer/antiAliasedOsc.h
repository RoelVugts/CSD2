#pragma once
#include <vector>

#include "oscillator.h"
#include "sine.h"

class AntiAliasedOsc : public Oscillator {
    public:
        AntiAliasedOsc();
        ~AntiAliasedOsc();

        void tick();

    protected:
        std::vector<Sine> partials;
        std::vector<float> partialSamples;
        int numHarmonics;


};


