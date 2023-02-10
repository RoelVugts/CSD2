
#include "complexMath.h"
#include <complex>
#include <cmath>
#include <iostream>

int main() 
{

    double pi = acos(-1);
    
    ComplexSystem firstOrder;
    firstOrder.setCoefficients(0.5, 0.5);

    // std::cout << "amplitude at half pi: " << firstOrder.amplitudeResponse(3*pi/4.0f, true) << " dB" << std::endl;

    double angle = pi/2;
    firstOrder.ampResponse(angle);
    firstOrder.phaseResponse(angle);

    return 0;
}