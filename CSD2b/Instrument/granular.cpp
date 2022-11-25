#include "granular.h"
#include "instrument.h"

#include <iostream>

using namespace std;

Granular::Granular()
{

}

Granular::Granular(float attackTime, float decayTime, float sustainLevel, float releaseTime, string sample, int grainSize, int density, float playbackSpeed)
: Sampler(attackTime, decayTime, sustainLevel, releaseTime, sample), grainSize(grainSize), density(density), playbackSpeed(playbackSpeed) 
{

}

Granular::~Granular()
{

}