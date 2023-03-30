
#include "filterResponse.h"
#include "circularBuffer.h"
#include "util.h"
#include "UI.h"

#include <complex>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>


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

    bool singleFrequency = askQuestion("Do you want to calcuate the response for a specific frequency[Y/n]?");
    float frequency = askQuestion("What is the frequency (range 0.0 to 6.238315307)?", 0.0f, 6.283185307f);
    if (singleFrequency)
    {
        std::cout << "Amplitude Response: " << Util::decibelsToGain(FIR.getResponse(frequency, "amplitude")) << " || " << FIR.getResponse(frequency, "amplitude") << " dB" << std::endl;
        std::cout << "Phase Response" << FIR.getResponse(frequency, "phase") << std::endl;
    }
  
    bool drawPlot = askQuestion("Do you want to draw the response in a plot?");
    if (drawPlot)
    {
        //Draw a graph showing amplitude and phase response
        FIR.plotResponse(10000, "amplitude");
        FIR.plotResponse(10000, "phase");
    }

    return 0;
}