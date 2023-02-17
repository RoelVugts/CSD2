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
        circBuf.input(input);
        float output = (1.0f - dryWet)*input + (dryWet * circBuf.output());
        return output;
    }

    void setDelayTime(int ms)
    {
        circBuf.setDistance(msToSamps(ms), true);
    }

    void setMaxDelay(int maxDelay)
    {
        circBuf.setSize(msToSamps(maxDelay));
    }

    int getDelayTime()
    {
        return circBuf.getDistance();
    }


    CircBuffer circBuf = CircBuffer(1);

private:

    float msToSamps(float ms)
    {
        return (ms/1000.0f) * sampleRate;
    }


    int sampleRate;
};
