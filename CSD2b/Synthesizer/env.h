#pragma once


#include <thread>
#include <vector>
#include "timer.h"

class Envelope {
    public:
        Envelope();
        Envelope(float attack, float decay, float sustain, float release);

        void triggerInThread();
        void setADSR(float attack, float decay, float sustain, float release);
        void trigger();
        float getLevel();
    
    protected:
        float attack;
        float decay;
        float sustain;
        float noteOnTime{1}; //Imagined 'note on' time
        float release;

        bool triggered{false};
        double elapsedTime;

        Timer envTimer;
        float level{1.0};

        std::thread t1;
};