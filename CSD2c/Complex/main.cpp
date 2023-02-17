
#include "filterResponse.h"

#include <complex>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

#define PI acos(-1)

int main() 
{

    Filter FIR;
    std::vector<double> coefficients;
    
    std::cout << "Enter amount of coefficients: ";
    int amount;
    std::cin >> amount;

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

    }

    FIR.setCoefficients(coefficients);

    //Draw a graph showing amplitude and phase response
    FIR.plotAmpResponse(10000);
    FIR.plotPhaseResponse(10000);



    return 0;
}