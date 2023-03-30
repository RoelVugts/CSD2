
#include "filterResponse.h"
#include "circularBuffer.h"
#include "util.h"
#include "UI.h"

#include <complex>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>


#define pi acos(-1)

int main() 
{
    Filter FIR;
    std::vector<double> coefficients;
    // 
    std::cout << "Enter amount of coefficients: ";
    int amount;
    std::cin >> amount;
// 
    for (int i = 0; i < amount; i++)
    {
        std::cout << "Enter value of coefficient " << i+1 << ": ";
        std::string input;
        std::cin >> input;
        try {
            double value = std::stod(input);
            coefficients.push_back(value);
        }
        catch (const std::exception& e) 
        {
            std::cout << "Value must be a number\n" << std::endl;
            i -= 1;
        }
// 
    }
// 
    FIR.setCoefficients(coefficients);
    int piDivisions = 0;
    piDivisions = askQuestion("How many divisions of pi do you want?", 1, 10000);
    double piStep = pi / piDivisions;
    for (int i = 0; i <= piDivisions; i++)
    {
        std::cout << "Pi / " << piDivisions << " x " << i << ": ";
        std::cout << std::setw(10) << "Amplitude Response: " << std::setw(10) << Util::decibelsToGain(FIR.getResponse(piStep*i, "amplitude")) << " || ";
        std::cout << std::setw(10) << FIR.getResponse(piStep*i, "amplitude") << " dB, ";
        std::cout << std::setw(10) << "   Phase Response: " << FIR.getResponse(piStep*i, "phase") << std::endl;
    }
  
    bool drawPlot = askQuestion("Do you want to draw the filter in a plot?");
    if (drawPlot)
    {
        //Draw a graph showing amplitude and phase response
        FIR.plotResponse(10000, "amplitude");
        FIR.plotResponse(10000, "phase");
    }

    return 0;
}