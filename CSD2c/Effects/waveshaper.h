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
        }

        float output(float input)
        {
            float index = (input + 1.0f) * (bufferSize * 0.5f); //make unipolar
            int i = (int)trunc(index);
            float decimal = index - (float)i;
            float shapedOutput = Util::linearMap(decimal, waveShape[i], waveShape[i + 1]);
            float output = (1.0f - dryWet)*input + (dryWet * shapedOutput);
            std::cout << "output: " << output << std::endl;
            return output;
        }

        void setDrive(float drive)
        {
            if (drive <= 0.0f)
                drive = 0.1f;
            for (int i = 0; i < bufferSize; i++)
            {
                float index = ((float)i/bufferSize) * 2 - 1;
                waveShape[i] = atan(drive * index) / atan(drive);
                std::cout << waveShape[i] << std::endl;
            }

        }

    private:
        float drive;
        float* waveShape;
        uint bufferSize { 512 };

};


