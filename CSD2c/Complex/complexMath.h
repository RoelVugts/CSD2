#include <complex>
#include <cmath>
#include <iostream>

#pragma once

class ComplexSystem {
    public:

        void setCoefficients(double a0, double a1)
        {
            this->a0 = a0;
            this->a1 = a1;
        }


        double ampResponse(double angle, bool dB = false)
        {
            std::complex<double> transfer = a0 + std::polar(a1, angle);
            std::cout << "Transfer: " << transfer << std::endl;
            double amplitude = complexMagnitude(transfer);
            std::cout << "Amplitude: " << amplitude << std::endl;
            std::cout << "Amplitude in dB: " << gainToDecibels(amplitude) << " dB" << std::endl;
            if (dB)
                return gainToDecibels(amplitude);
            else
                return amplitude;
        }

        double phaseResponse(double angle)
        {
            std::complex<double> transfer = a0 + std::polar(a1, angle);
            double phase = complexAngle(transfer);
            std::cout << "Phase: " << phase << std::endl;
            return phase;
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

        inline double calcMagnitude(double x, double y)
        {   
            double magnitude = std::sqrt(pow(x,2.0) + pow(y,2.0));
            return magnitude;
        }

        inline double gainToDecibels(double gain)
        {
            return 20.0f * log10(gain/1.0);
        }


        double a0, a1; //a0 = x[n] || a1 = x[n-1]
        double e = exp(1);
        double pi = acos(-1);
        std::complex<double> i {0.0, 1.0};

};




// #include <cmath>
// #include <complex>
// #include <vector>

// double amplitude_response(const std::vector<double>& coefficients, double angle)
// {
//     std::complex<double> sum, e;

//     sum = 0;
//     for (int j = 0; j < coefficients.size(); j++)
//     {
//         e = std::complex<double>(cos(angle * j), sin(angle * j));
//         sum += coefficients[j] * e;
//     }

//     return abs(sum);
// }
