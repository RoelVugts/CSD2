#ifndef CALLBACK_H
#define CALLBACK_H

#include "jack_module.h"
#include "oscillator.h"
#include "sine.h"
#include "sawtooth.h"
#include "square.h"
#include "antiAliasedOsc.h"
#include "antiAliasedSquare.h"
#include "antiAliasedSaw.h"
#include "superSynth.h"
#include "FmSynth.h"
#include "synth.h"

class CustomCallback : public AudioCallback {
public:
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;


  void setSynth(Synth* synth);
private:
  float samplerate = 48000;
  // AntiAliasedSquare aSquare = AntiAliasedSquare();
  Synth* synth;

  // Square square = Square(500, 0.5); 
  
};



#endif //CALLBACK_H

