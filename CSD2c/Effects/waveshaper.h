#include "effect.h"
#include "Util.h"
#include <cmath>

#pragma once

using uint = unsigned int;

class Waveshaper : public Effect {
    public:

        Waveshaper() {}

        void prepareToPlay(int sampleRate)
        {
            waveShape = new float[bufferSize];
            setDrive(10.0f);
            // bitCrusher(6);
            setAssymetry(1.0f);
            clipDist();
        }

        float output(float input)
        {
            float index = (input + 1.0f) * (bufferSize * 0.5f); //make unipolar
            int i = (int)trunc(index);
            float decimal = index - (float)i;
            float shapedOutput = Util::linearMap(decimal, waveShape[i], waveShape[i + 1]);
            float output = (1.0f - dryWet)*input + (dryWet * shapedOutput);
            return output;
        }

        void setDrive(float drive)
        {
            if (drive <= 0.0f)
                this->drive = 0.1f;
            else
                this->drive = drive;
        }

        void bitCrusher(int bitDepth)
        {

            double step = 2.0f / (pow(2.0, bitDepth) - 1.0);

            for (int i = 0; i < bufferSize; i++)
            {
                float index = ((float)i/bufferSize) * 2.0 -1.0;
                waveShape[i] = step * (int)(index/step);

            }
        }

        void setAssymetry(float assymetry)
        {
            if (assymetry >= 0.0f)
            {
                posDrive = 1.0f / (1.0f - assymetry);
                negDrive = 1.0f;
            } else {
                negDrive = 1.0f / (1.0f + assymetry);
                posDrive = 1.0f;
            }
        }

        void clipDist()
        {
            for (int i = 0; i < bufferSize; i++)
            {
                float index = ((float)i/bufferSize) * 2 - 1; //scale i between -1.0 and + 1.0
                
                if (index < 0.0f)
                    waveShape[i] = atan(drive * index) / (atan(drive) * posDrive); //transfer function
                else if (index > 0.0f)
                    waveShape[i] = atan(drive * index) / (atan(drive) * negDrive); //transfer function
                else
                    waveShape[i] = 0.0f;
                std::cout << "Input: " << index << "               "; 
                std::cout << "output: " << waveShape[i] << std::endl;
            }
        }

    private:
        float drive;
        float* waveShape;
        uint bufferSize { 512 };
        float posDrive { 1.0f }, negDrive { 1.0f };

};


