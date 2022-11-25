#include "synth.h"
#include "instrument.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <unistd.h>

using namespace std;

Synth::Synth() : Synth(10, 0, 1.0, 20, "Sine", 440, 1.0, 0) 
{

}

Synth::Synth(float attackTime, float decayTime, float sustainLevel, float releaseTime, string oscillator, float freq, float amp, float phase) 
: Instrument(attackTime,  decayTime,  sustainLevel,  releaseTime), oscillator(oscillator), freq(freq), amp(amp), phase(phase)
{
   if(oscillator == "Sine") {
    this->sound = "Tuuuuuuuuuuuu...";
   } else if (oscillator == "Square") {
    this->sound = "toeeeeeeeeeeeee...";
   } else if (oscillator == "Saw") {
    this->sound = "Buzzzzzzzz....";
   };
}

void Synth::setOscillator(string oscillator) {
    if(oscillator == "Sine") {
    this->sound = "Tuuuuuuuuuuuu...";
    } else if (oscillator == "Square") {
    this->sound = "toeeeeeeeeeeeee...";
    } else if (oscillator == "Saw") {
    this->sound = "Buzzzzzzzz....";
    } else {
        this->oscillator = oscillator;
    };
}

string Synth::getOscillator() {
    return oscillator;
}

void Synth::setFreq(float freq) {
    this->freq = freq;
}

float Synth::getFreq() {
    return freq;
}

void Synth::setAmp(float amp) {
    this->amp = amp;
}

float Synth::getAmp() {
    return amp;
}

void Synth::setPhase(float phase) {
    this->phase = phase;
}

float Synth::getPhase() {
    return phase;
}
