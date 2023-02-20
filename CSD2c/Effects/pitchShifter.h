#include "effect.h"

#include "delay.h"

#pragma once

class PitchShifter : public Effect {
    public:

        void prepareToPlay(int sampleRate) override
        {
            delay.prepareToPlay(sampleRate);
            this->sampleRate = sampleRate;
            pitch = -5;
        }

        float output(float input) override
        {
            ramp();
            delay.setDelayTime(50 * line);
            return delay.output(input);

        }

        void ramp()
        {   
            line = line + pitch / sampleRate;

            if (line > 1.0f)
                line -= 1.0f;
        }

    private:
        Delay delay = Delay();
        float line = 0.0f;
        float pitch = 0.0f;
        int sampleRate;


};