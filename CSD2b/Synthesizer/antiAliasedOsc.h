#pragma once
#include <vector>

#include "oscillator.h"
#include "sine.h"

class AntiAliasedOsc : public Oscillator {
    public:
        AntiAliasedOsc();
        AntiAliasedOsc(float frequency, float amplitude);
        ~AntiAliasedOsc();

        void setFrequency(float frequency); //override function becasuse in the antiAliasedOsc we need to recalculate partials
        void tick();


    protected:
        std::vector<Sine> partials;
        std::vector<float> partialSamples;
        int numHarmonics;

        virtual void calculate() = 0; //Abstract method
        virtual void createPartials() = 0; //Create elements of partials in vector
        virtual void calculatePartials() = 0; //recalculate frequency of partials


};


