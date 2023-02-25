#include <complex>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cstdio>

#pragma once

class Filter {
    public:

        Filter() {}
        ~Filter() { remove("response.csv"); }

        //sets the filters coefficients
        void setCoefficients(std::vector<double> values)
        {
            coefficients.clear();
            std::vector<double>::iterator i = values.begin();
            while (i != values.end())
            {
                coefficients.push_back(*i);
                i++;
            }
        }

        //Returns the amplitude response of a given frequency 
        double getResponse(double angle, std::string type)
        {
            std::complex<double> transferSum = {0.0, 0.0}; //initialize variable
            std::vector<double>::iterator i = coefficients.begin();
            i++; //skip first coefficient since this is not a complex number
            double n = 1.0; //Index for the nth sample delay in the filter (n-1) (n-2) etc...
            while (i != coefficients.end())
            {
                transferSum += std::polar(*i, angle * -1 * n);
                i++;
                n++;
            }

            transferSum += coefficients[0];
            if (type == "amplitude")
                return gainToDecibels(abs(transferSum));
            else if (type == "phase")
                return arg(transferSum);
        }

        void plotResponse(int numPoints, std::string type)
        {
            double angle = 0.0;
            double angleDelta = pi/(numPoints-1);
            ampPlot.open("response.csv", std::ofstream::out | std::ofstream::trunc);
            for (int i = 0; i < numPoints; i++)
            {
                ampPlot << getResponse(angle, type) << std::endl;
                angle += angleDelta;
            }
            ampPlot.close();
            std::string command = "python3 plot.py " + type;
            std::system(command.c_str());
        }        

    private:

        inline std::complex<double> carToPol(std::complex<double> z)
        {
            std::complex<double> zPolar(abs(z), arg(z));
            return zPolar;
        }

        inline double gainToDecibels(double gain)
        {
            return 20.0f * log10(gain/1.0);
        }

        std::vector<double> coefficients;
        double e = exp(1);
        double pi = acos(-1);
        std::complex<double> i { 0.0, 1.0 };
        std::ofstream ampPlot;
        std::ofstream phasePlot;
};