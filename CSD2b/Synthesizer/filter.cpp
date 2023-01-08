#include "filter.h"

#include <vector>
#include <cmath>


float Filter::lowpass(float inputValue) {
    output += cutoff * (inputValue - output); //y(n) = y(n-1) + a_{0}[ x(n) - y(n-1) ] https://docs.cycling74.com/max7/refpages/onepole~
    output2 += cutoff * (output - output2); //2nd order lowpass
    return output2;
}

float Filter::highpass(float inputValue) {
    output += cutoff * (inputValue - output);
    output2 += cutoff * (output - output2); 
    return inputValue - output2; //subtract original signal from lowpass signal to get highpass signal
}

void Filter::setCutoff(float cutoff)
{
    this->cutoff = sin(cutoff*(M_PI/48000)); //calculate cutoff -> https://docs.cycling74.com/max7/refpages/onepole~
}