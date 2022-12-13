#include "callback.h"
#include "sine.h"
#include "sawtooth.h"
#include "square.h"
#include "synth.h"
#include "superSynth.h"


#include <iostream>

void CustomCallback::prepare(int rate) {
    samplerate = (float) rate;
    // superSaw.setSamplerate(samplerate);
    std::cout << "\nsamplerate: " << samplerate << "\n";
}

void CustomCallback::process(AudioBuffer buffer) {
  for (int i = 0; i < buffer.numFrames; ++i) {
    // write sample to buffer at channel 0, amp = 0.25
    buffer.outputChannels[0][i] = superSynth.getSample();
    superSynth.tick();
  }
}
