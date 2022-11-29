#pragma once

#include <cmath>

using namespace std;

class SineOscillator {
    public:
        SineOscillator();
        SineOscillator(float freq, float amp);
        ~SineOscillator();

    double play();

    double getSampleValue();
    
    
    protected:
        float freq;
        float amp;
        double sampleValue = 0;

    
    private:
        float angle = 0.0;
        float offset = ((2 * M_PI * freq) / 44100);
};