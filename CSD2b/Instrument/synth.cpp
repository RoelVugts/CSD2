#include "synth.h"
#include "instrument.h"
#include <cmath>
#include <iostream>
#include <unistd.h>

using namespace std;

Synth::Synth() : Synth(10, 0, 1.0, 20, "Sine", 440, 1.0, 0) 
{

}

Synth::Synth(float attackTime, float decayTime, float sustainLevel, float releaseTime, string oscillator, float freq, float amp, float phase)
{
    this->attackTime = attackTime;
    this->decayTime = decayTime;
    this->sustainLevel = sustainLevel;
    this->releaseTime = releaseTime;
    this->oscillator = "Sine";
    this->freq = freq;
    this->amp = amp;
    this->phase = phase;

}

void Synth::setOscillator(string oscillator) {
    if(oscillator == "Sine" || oscillator == "Square" || oscillator == "Saw") {
        this->oscillator = oscillator;
    } else {
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

float Synth::play(float i) {
    double sample;
    if(oscillator == "Sine") {
        sample = sin(2*3.14*freq*i+phase);
    };

    if(oscillator == "Square") {
        sample = (fmod(i,2.0)) * 2.0 - 1.0;
    };

    if(oscillator == "Saw") {
        sample = fmod((i/10),1.0);
    }
    return sample;

}

