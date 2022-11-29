#pragma once

class Oscillator {
    public:
        Oscillator();
        Oscillator(float frequency, float amplitude, float phase, float samplerate);
        ~Oscillator();

        void setSamplerate(float samplerate);
        float getSample();

        //getters and setters
        void setFrequency(float frequency);
        float getFrequency();

    protected:
        float frequency;
        float amplitude;
        float phase;
        float sample;
        float samplerate;
};