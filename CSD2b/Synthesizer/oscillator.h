#pragma once

#define SAMPLERATE 48000

class Oscillator {
    public:
        Oscillator();
        Oscillator(float frequency, float amplitude, float phase, float samplerate);
        Oscillator(float frequency, float amplitude);
        ~Oscillator();

        void setSamplerate(float samplerate);
        float getSample();
        
        float getSampleRate();

        //getters and setters
        void setFrequency(float frequency);
        float getFrequency();

    protected:
        float frequency;
        float amplitude;
        float phase;
        float sample;
        float samplerate = SAMPLERATE;
};