#pragma once

#include "antiAliasedOsc.h"

class AntiAliasedSaw : public AntiAliasedOsc {
    public:
        AntiAliasedSaw();
        AntiAliasedSaw(float frequency, float amplitude);
        ~AntiAliasedSaw();
    
    void calculate();


    private:
        void createPartials();
};