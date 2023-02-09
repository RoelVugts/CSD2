//
// Created by Dean on 27/10/2022.
//
#pragma once

#include "effect.h"
#include "EmptyCircBuffer.h"

class Delay : Effect {
public:
    Delay() {}
    ~Delay() {}
    void prepareToPlay (int sampleRate) override {
        this->sampleRate = sampleRate;
        circBuf.setSize(sampleRate*2);
        circBuf.setDistance(msToSamps(1000));

    }

    float input (float input) override {
        circBuf.incrementHeads();
        circBuf.input(input);

        // std::cout << "ReadPos: " << circBuf.getReadPosition() << std::endl;
        // std::cout << "WritePos: " << circBuf.getWritePosition() << std::endl;
        // std::cout << "input: " << input << std::endl; 
    }

    float output()
    {
        // std::cout << "Output: " << circBuf.output() << std::endl;
        return circBuf.output();
    }

    void setDelayTime(int ms)
    {
        circBuf.setDistance(msToSamps(ms));
    }

    void setMaxDelay(int maxDelay)
    {
        circBuf.setSize(msToSamps(maxDelay));
    }

    int getDelayTime()
    {
        return circBuf.calculateDistance();
    }


    CircBuffer circBuf = CircBuffer(1);

private:

    int msToSamps(int ms)
    {
        return (ms/1000.0f) * sampleRate;
    }


    int sampleRate;
};
