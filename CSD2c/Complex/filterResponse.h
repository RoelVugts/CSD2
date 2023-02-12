#include <complex>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#pragma once

class Filter {
    public:

        Filter() {}
        ~Filter() {}

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
        double ampResponse(double angle, bool dB = false)
        {
            std::complex<double> transferSum = {0.0, 0.0};
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

            double amplitude = complexMagnitude(transferSum);
            if (dB)
                return gainToDecibels(amplitude);
            else
                return amplitude;
        }

        //Returns the phase response of a given frequency
        double phaseResponse(double angle)
        {

            std::complex<double> transferSum = {0.0, 0.0};
            std::vector<double>::iterator i = coefficients.begin();
            i++;
            double n = 1.0;

            while (i != coefficients.end())
            {
                transferSum += std::polar(*i, angle * -1 * n);
                i++;
                n++;
            }

            transferSum += coefficients[0];
            double phase = complexAngle(transferSum);
            return phase;
        }

        //Calculates amplitude response for numPoints from 0 to 2π and plots it on a graph
        void plotAmpResponse(int numPoints)
        {
            double angle = 0.0;
            double angleDelta = 2*pi/numPoints;
            ampPlot.open("response.csv", std::ofstream::out | std::ofstream::trunc);
            for (int i = 0; i < numPoints; i++)
            {
                ampPlot << ampResponse(angle, true) << std::endl;
                angle += angleDelta;
            }
            ampPlot.close();
            std::string type = "amplitude";
            std::string command = "python3 plot.py " + type;
            std::system(command.c_str());
        }

        //Calculates phase response for numPoints from 0 to 2π and plots it on a graph
        void plotPhaseResponse(int numPoints)
        {
            double angle = 0.0;
            double angleDelta = 2*pi/numPoints;
            phasePlot.open("response.csv", std::ofstream::out | std::ofstream::trunc);
            for (int i = 0; i < numPoints; i++)
            {
                phasePlot << phaseResponse(angle) << std::endl;
                angle += angleDelta;
            }
            phasePlot.close();
            std::string type = "phase";
            std::string command = "python3 plot.py " + type;
            std::system(command.c_str());
        }
        

    private:

        inline std::complex<double> polToCar(std::complex<double> z)
        {
            std::complex<double> zCartesian (real(z)*cos(imag(z)), real(z)*sin(imag(z)));
            return zCartesian;
        }

        inline double complexAngle(std::complex<double> z)
        {
            double angle = atan2(imag(z), real(z));
            return angle;
        }

        inline double complexMagnitude(std::complex<double> z)
        {   
            double magnitude = std::sqrt(pow(real(z),2.0) + pow(imag(z),2.0f));
            return magnitude;
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