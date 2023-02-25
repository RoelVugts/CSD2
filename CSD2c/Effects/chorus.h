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

        float output(float input, uint channel = 0)
        {
            tick(channel);

            return input * (1 - dryWet) + delays[channel].output(input) * dryWet;
        }

        void tick(uint channel)
        {
            lfos[channel].tick();
            float modulation = delayTime + depth * lfos[channel].getSample();
            delays[channel].setDelayTime(modulation);
        }


    private:
        float rate { 5.0f };
        Delay delays[2] = {Delay(), Delay()};
        Sine lfos[2] = { Sine(rate, 0.5f), Sine(rate, 0.0f) };
        float depth { 5.0f };
        float delayTime { 25.0f };
        float sampleRate;

};