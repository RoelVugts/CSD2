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

class CustomCallback : public AudioCallback {
public:
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;

  // Sine sine = Sine(500, 0.5);
    // AntiAliasedSaw aSaw = AntiAliasedSaw();
    // Sawtooth saw1 = Sawtooth(500, 0.5);
    SuperSynth superSynth = SuperSynth(800, 1.0, 5, 50);
    // AntiAliasedSquare aSquare = AntiAliasedSquare(500, 1.0);
    FmSynth fmSynth = FmSynth(1000, 1.0);
private:
  float samplerate = 48000;
  // AntiAliasedSquare aSquare = AntiAliasedSquare();


  // Square square = Square(500, 0.5); 
  
};



#endif //CALLBACK_H

