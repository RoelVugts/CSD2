#include "effect.h"
#include "delay.h"
#include "sine.h"

#pragma once

class Chorus : public Effect {
    public:
        Chorus() {}

        void prepareToPlay(int sampleRate) override
        {
            for (Delay& delay : delays)
            {
                delay.prepareToPlay(sampleRate);
                delay.setMaxDelay(50);
                delay.setDelayTime(delayTime);
            }

            for (Sine& lfo : lfos)
                lfo.setSamplerate(sampleRate);
            
            lfos[1].setPhase(0.5); //180 degrees phase shift on right channel LFO

            this->sampleRate = sampleRate;
        }

        float output(float input) override
        {
            tick();
            
            return input * (1.0f - dryWet) + delays[0].output(input) * dryWet + delays[1].output(input) * dryWet;
        }

        float output(float input, int channel)
        {
            tick();
            return input * (1 - dryWet) + delays[channel].output(input) * dryWet;
        }

        void tick()
        {
            for (int channel = 0; channel < 2; channel++)
            {
                lfos[channel].tick();
                float modulation = delayTime + depth * lfos[channel].getSample();
                delays[channel].setDelayTime(modulation);
                // std::cout << "Modulation: " << modulation << std::endl;
            }
        }


    private:
        float rate { 0.5f };
        Delay delays[2] = {Delay(), Delay()};
        Sine lfos[2] = { Sine(rate, 0.5f), Sine(rate, 0.5f) };
        float depth { 10.0f };
        float delayTime { 25.0f };
        float sampleRate;

};