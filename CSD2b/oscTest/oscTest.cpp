#include "oscTest.h"

#include <iostream>
#include <cmath>
#include <fstream>


using namespace std;

SineOscillator::SineOscillator() : freq(400), amp(0.5)
{
    cout << "Constructed default oscillato\n" << endl;
}

SineOscillator::SineOscillator(float freq, float amp) : freq(freq), amp(amp)
{
    cout << "Constructed oscillator with freq: " << freq << " and amp: " << amp << "\n" << endl;
}

SineOscillator::~SineOscillator()
{
    cout << "Deconstructor\n" << endl;
}

double SineOscillator::play()
{
    angle = angle + offset;
    sampleValue = amp * sin(angle);
    return sampleValue;
}

double SineOscillator::getSampleValue()
{
    return sampleValue;
}