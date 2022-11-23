#include "granular.h"
#include "instrument.h"

#include <iostream>

using namespace std;

Granular::Granular()
{

}

Granular::Granular(float attackTime, float decayTime, float sustainLevel, float releaseTime, string oscillator, float freq, float amp, float phase, int grainSize, int density, float playbackSpeed)
: Synth(attackTime, decayTime, sustainLevel, releaseTime, oscillator, freq, amp, phase), grainSize(grainSize), density(density), playbackSpeed(playbackSpeed) 
{

}

Granular::~Granular()
{

}