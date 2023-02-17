#include "effect.h"
#include "sine.h"

#pragma once

class Tremolo : public Effect {
    public:
        Tremolo()
        {
            frequency = 5.0f;
            dryWet = 1.0f;
        }

        ~Tremolo() {}

        void prepareToPlay(int sampleRate) override
        {
            this->sampleRate = sampleRate;
            sine.setSamplerate(sampleRate);
            sine.setAmplitude(1.0f);
            sine.setFrequency(frequency);
        }

        float output(float input)
        {
            sine.tick();
            float modulator = (sine.getSample() + 1.0f) / 2.0f; //make unipolar
            float output = input * ((1.0f - dryWet) + (dryWet * modulator));
            return output;
        }

        void setFrequency(float frequency)
        {
            this->frequency = frequency;
            sine.setFrequency(frequency);
        }



    private:
        Sine sine = Sine(frequency, dryWet);
        int sampleRate;
        float frequency { 10.0f };
};