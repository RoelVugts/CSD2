#include "perc_synth.h"

using namespace std;

PercSynth::PercSynth() : PercSynth(0,0,0,0, "niks", "Saw", 400, 1, 0)
{

}

PercSynth::PercSynth(float attackTime, float decayTime, float sustainLevel, float releaseTime, string type, string oscillator, float freq, float amp, float phase)
:   Percussion(attackTime, decayTime, sustainLevel, releaseTime, type),  Synth(attackTime, decayTime, sustainLevel, releaseTime, oscillator, freq, amp, phase)
{

}

PercSynth::~PercSynth()
{

}