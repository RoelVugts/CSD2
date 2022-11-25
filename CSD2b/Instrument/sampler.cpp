#include "sampler.h"
#include "instrument.h"

using namespace std;

Sampler::Sampler() : Sampler(0,0,0,0, "No sample") //default constructor
{

}

Sampler::Sampler(float attackTime, float decayTime, float sustainLevel, float releaseTime, string sample) 
: Instrument(attackTime, decayTime, sustainLevel, releaseTime), sample(sample)
{
    this->sound = sample;
}

Sampler::~Sampler()
{
    //Deconstructor
}

void Sampler::setSample(string sample) 
{
    this->sample = sample;
}

string Sampler::getSample()
{
    return sample;
}

void Sampler::setPitch(int pitch)
{
    this->pitch = pitch;
}

int Sampler::getPitch()
{
    return pitch;
}