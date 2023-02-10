
#include "filterResponse.h"

#include <complex>
#include <cmath>
#include <iostream>
#include <fstream>

#define PI acos(-1)


int main() 
{
    Filter firstOrder;
    
    firstOrder.setCoefficients(0.5, 0.5);

    std::cout << "Amplitude response at angle pi/2 is: " << firstOrder.ampResponse(PI/2, true) << " dB" << std::endl;
    std::cout << "Phase response at angle pi/6 is: " << firstOrder.phaseResponse(PI/6) << " radians" << std::endl;

    firstOrder.plotAmpResponse(10000);
    firstOrder.plotPhaseResponse(10000);

    return 0;
}