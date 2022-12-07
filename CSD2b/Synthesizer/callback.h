#ifndef CALLBACK_H
#define CALLBACK_H

#include "jack_module.h"
#include "oscillator.h"
#include "sine.h"
#include "sawtooth.h"
#include "square.h"
#include "organSynth.h"
#include "antiAliasedOsc.h"
#include "antiAliasedSquare.h"
#include "antiAliasedSaw.h"

class CustomCallback : public AudioCallback {
public:
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;


private:
  float samplerate = 48000;
  // AntiAliasedSquare aSquare = AntiAliasedSquare();
  // Sine sine = Sine(500, 0.5);
  // Sawtooth saw = Sawtooth(500, 0.5);
  // Square square = Square(500, 0.5); 
  AntiAliasedSaw aSaw = AntiAliasedSaw(1000, 1.0);
};



#endif //CALLBACK_H

