#include "effect.h"
#include "sine.h"

class Tremolo : public Effect {
    public:
        Tremolo(float frequency, float dryWet) : frequency(frequency) 
        {
            this->dryWet = dryWet;
        }

        ~Tremolo() {}

        void prepareToPlay(int sampleRate) override
        {
            this->sampleRate = sampleRate;
            sine.setSamplerate(sampleRate);
        }

        float output(float input)
        {
            sine.tick();
            float output = input * ((1.0f - dryWet) + (dryWet * sine.getSample()));
            return output;
        }

        void setFrequency(float frequency)
        {
            this->frequency = frequency;
        }

    private:
        Sine sine = Sine(frequency, dryWet);
        int sampleRate;
        float frequency { 10.0f };
};