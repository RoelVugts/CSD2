#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

#define SAMPLERATE 24000

class BlepOsc {
  public:
    double polyBLEP(double t);
    double getSample();
    void tick();

    double freq = 10000;
    double phaseIncrement = freq / SAMPLERATE;
    const double twoPI = acos(-1)*2;
    double sample = 0.0;
    double phase = 0.0;
};


double BlepOsc::polyBLEP(double t)
{
    double dt = phaseIncrement;
    if (t < dt) 
    {
        t /= dt;
        // std::cout << "t: " << std::setw(10) << t << std::endl;
        return t+t - t*t - 1.0;
    }
    else if (t > 1.0 - dt) 
    {
        t = (t - 1.0) / dt;
        return t*t + t+t + 1.0;
    }
    else return 0.0;

}

double BlepOsc::getSample()
{
  return sample;
}

void BlepOsc::tick()
{
  phase += phaseIncrement;
  if(phase > 1.0)
  {
    phase -= 1.0;
  }

  if (phase < 0.5)
  {
    sample = 1.0;
  } else 
  {
    sample = -1.0;
  }

  // sample = phase * 2.0 - 1.0;
  sample += polyBLEP(phase);
  sample -= polyBLEP(fmod(phase + 0.5, 1.0));
}


/*


double t = 0.; // 0 <= t < 1
double dt = freq / sampleRate;
 

 
double poly_blep(double t, double dt)
{
  // 0 <= t < 1
  if (t < dt)
  {
    t /= dt;
    // 2 * (t - t^2/2 - 0.5)
    return t+t - t*t - 1.;
  }
 
  // -1 < t < 0
  else if (t > 1. - dt)
  {
    t = (t - 1.) / dt;
    // 2 * (t^2/2 + t + 0.5)
    return t*t + t+t + 1.;
  }
 
  // 0 otherwise
  else
  {
    return 0.;
  }
}
 
double poly_saw(double t, double dt)
{
  // Correct phase, so it would be in line with sin(2.*M_PI * t)
  t += 0.5;
  if (t >= 1.) t -= 1.;
 
  double naive_saw = 2.*t - 1.;
  return naive_saw - poly_blep(t, dt);
}

int main()
{

    std::ofstream graph("output.csv");

    for(int i = 0; i < sampleRate*5; ++i)
    {
        sample = poly_saw(t, dt);
        t += dt;
        graph << sample << std::endl;
    }



    graph.close();
    return 0;
}

*/ 