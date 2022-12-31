#include "blep.h"



int main()
{

BlepOsc osc;
  
    std::cout << "PhaseIncrement: " << osc.phaseIncrement << std::endl;
    std::ofstream plot("output.csv");

    for(int i = 0; i < SAMPLERATE/(osc.freq/4); i++)
    {
      std::cout << "Phase: " << osc.phase << std::setw(20) << "BLEP: " << osc.polyBLEP(osc.phase) << std::setw(20) << "Sample: " << osc.sample << std::endl;
      osc.tick();

      plot << osc.getSample() << std::endl;
    }
    plot.close();

    return 0;
}