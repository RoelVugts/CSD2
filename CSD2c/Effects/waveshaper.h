#include "effect.h"
#include "Util.h"
#include <cmath>

using uint = unsigned int;

class Waveshaper : public Effect {
    public:

        Waveshaper(uint bufferSize) : waveShape(new double[bufferSize]) {}

        float input(float input)
        {
            

        }


        float output(float input)
        {
            double abs = (input + 1.0f) / 2.0f;
            int index = bufferSize * abs;
            double low = waveShape[index];
            double high = waveShape[index + 1];
            double output = Util::linearMap(abs, low, high);
            return output;
        }

        void setDrive(float drive)
        {
            for (int i = 0; i < bufferSize; i++)
            {
                waveShape[i] = pow(i/bufferSize, drive);
            }

        }

    private:
        float drive;
        double* waveShape;
        uint bufferSize;

};


