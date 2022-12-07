#pragma once

#include <cmath>
#include <vector>


class Oscillator {
    public:
        Oscillator();
        Oscillator(float frequency, float amplitude);
        ~Oscillator();

        //getters and setters
        void setFrequency(float frequency);
        float getFrequency();
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