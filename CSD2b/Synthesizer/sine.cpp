#include "sine.h"
#include "math.h"

Sine::Sine() : Oscillator(440, 0.5, 0, 4800)
{
  
}

Sine::Sine(float frequency, float amplitude, float phase, float samplerate) : Oscillator(frequency, amplitude, phase, samplerate)
{
  std::cout << "Sine - constructor\n";
}

Sine::Sine(float frequency, float amplitude) : Oscillator(frequency, amplitude)
{
  phase = 0;
  samplerate = 48000;
}


Sine::~Sine() {
  std::cout << "Sine - destructor\n";
}

void Sine::calculate() 
{

  sample = sin(M_PI * 2 * phase) * amplitude;

}