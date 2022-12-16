#include "callback.h"
#include "sine.h"
#include "sawtooth.h"
#include "square.h"
#include "synth.h"
#include "superSynth.h"
#include "FmSynth.h"


#include <iostream>

void CustomCallback::prepare(int rate) {
    samplerate = (float) rate;
    // superSaw.setSamplerate(samplerate);
    std::cout << "\nsamplerate: " << samplerate << "\n";
}

void CustomCallback::process(AudioBuffer buffer) {
  for (int i = 0; i < buffer.numFrames; ++i) {
    // write sample to buffer at channel 0, amp = 0.25
    buffer.outputChannels[0][i] = synth->getSample();
    synth->tick();
  }
}

//function to set the synth the user chose
void CustomCallback::setSynth(Synth* synth)
{
  this->synth = synth;
}