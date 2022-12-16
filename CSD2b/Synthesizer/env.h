#pragma once


#include <thread>
#include "timer.h"

class Envelope {
    public:
        Envelope();
        Envelope(float attack, float decay, float sustain, float release);


        void setADSR(float attack, float decay, float sustain, float release);
        void trigger();
        void triggerInThread();
        float getLevel();
    
    protected:
        float attack;
        float decay;
        float sustain;
        float noteOnTime{50}; //Imagined 'note on' time
        float release;

        bool triggered;
        double elapsedTime;

        Timer envTimer;
        float level{1.0};
        std::thread t;
};