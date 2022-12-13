#pragma once

#include <cmath>
#include <vector>


class Oscillator {
    public:
        Oscillator();
        Oscillator(float frequency, float amplitude);
        ~Oscillator();

        //getters and setters
        virtual void setFrequency(float frequency); //virtual because we override function in AntiAliasedOsc
        float getFrequency();
        virtual void setAmplitude(float amplitude);
        float getSample();
        float getSampleRate();
        void setSamplerate(float samplerate);

        virtual void tick();

    protected:
        float samplerate;
        float frequency;
        float amplitude;
        float phase;
        float sample;
        int voices;
        double pi = acos(-1);

        virtual void calculate() = 0;

};