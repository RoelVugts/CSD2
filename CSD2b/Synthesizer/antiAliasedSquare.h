#pragma once

#include "antiAliasedOsc.h"

class AntiAliasedSquare : public AntiAliasedOsc {
    public:
        AntiAliasedSquare();
        AntiAliasedSquare(float frequency, float amplitude);
        ~AntiAliasedSquare();

    void calculate();
    protected:

};