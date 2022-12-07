#include "sine.h"
#include "math.h"

#include <iostream>

Sine::Sine() : Oscillator()
{
  std::cout << "Constructed default sine" << std::endl;
}

Sine::Sine(float frequency, float amplitude) : Oscillator(frequency, amplitude)
{
  std::cout << "Constructed sine with frequency: " << frequency << " and amplitude: " << amplitude << std::endl;
}


Sine::~Sine() 
{
  std::cout << "Sine - destructor\n";
}

void Sine::calculate() 
{

  sample = sin(pi * 2 * phase) * amplitude;

}