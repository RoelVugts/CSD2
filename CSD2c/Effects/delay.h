//
// Created by Dean on 27/10/2022.
//
#pragma once

#include "effect.h"
#include "CircularBuffer.h"

class Delay : public Effect {
public:
    Delay() {}
    ~Delay() {}

    void prepareToPlay (int sampleRate) override {
        this->sampleRate = sampleRate;
        circBuf.setSize(sampleRate*2);
        circBuf.setDistance(msToSamps(1000), false);

    }

    float output(float input)
    {
        circBuf.incrementHeads();
        circBuf.input(input + feedback * circBuf.output());
        float output = (1.0f - dryWet)*input + (dryWet * circBuf.output());
        return output;
    }

    void setDelayTime(float ms)
    {
        circBuf.setDistance(msToSamps(ms), false);
    }

    void setMaxDelay(int maxDelay)
    {
        circBuf.setSize(msToSamps(maxDelay));
    }

    double getDelayTime()
    {
        return circBuf.getDistance();
    }

    void setFeedback(float feedback)
    {
        if (feedback > 0.9f)
            this->feedback = 0.9f;
        else if (feedback < -0.9f)
            this->feedback = -0.9f;
        else
            this->feedback = feedback;
    }


    CircBuffer<float, float> circBuf = CircBuffer<float, float>(1);

private:

    float msToSamps(float ms)
    {
        return (ms/1000.0f) * sampleRate;
    }

    int sampleRate;
    float feedback { 0.0f };
};
