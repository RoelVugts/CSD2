#ifndef CALLBACK_H
#define CALLBACK_H

#include "jack_module.h"
#include "oscillator.h"
#include "sine.h"
#include "sawtooth.h"
#include "square.h"

class CustomCallback : public AudioCallback {
public:
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;

private:
  float samplerate = 44100;
  Sine sine = Sine(500, 0.5);
  Sawtooth saw = Sawtooth(500, 0.5);
  Square square = Square(500, 0.5); 
};



#endif //CALLBACK_H

