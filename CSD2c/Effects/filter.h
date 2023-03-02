#include "effect.h"
#include "CircularBuffer.h"
#include <cmath>
#include <iostream>

class Filter : public Effect {
    public:

        virtual void prepareToPlay(int samplerate) override
        {
            this->samplerate = samplerate;
        }

        virtual float output(float input) override
        {
            if (mode == 0)
                return lowpass(input);
            if (mode == 1)
                return highpass(input);
            if (mode == 2)
                return allpass(input);
            else 
                return 0.0f;
        }


        void setCutoff(float cutoff)
        {
            if (cutoff > samplerate/2)
                cutoff = samplerate/2;
            else if (cutoff < 0)
                cutoff = 0.0;

            this->cutoff = sin(cutoff*(M_PI/samplerate)); //calculate cutoff -> https://docs.cycling74.com/max7/refpages/onepole~
        }

        void setMode(std::string mode)
        {
            if (mode == "lowpass")
                this->mode = 0;
            else if (mode == "highpass")
                this->mode = 1;
            else
                std::cout << "No valid filter mode entered" << std::endl;
        }

        float lowpass(float inputValue) 
        {
            output1 += cutoff * (inputValue - output1); //y(n) = y(n-1) + a_{0}[ x(n) - y(n-1) ] https://docs.cycling74.com/max7/refpages/onepole~
            output2 += cutoff * (output1 - output2); //2nd order lowpass
            return output2;
        }

        float highpass(float inputValue) 
        {
            output1 += cutoff * (inputValue - output1);
            output2 += cutoff * (output1 - output2); 
            return inputValue - output2; //subtract original signal from lowpass signal to get highpass signal
        }

        float allpass(float inputValue)
        {
            circBuf.input(inputValue);
            std::cout << "input: " << inputValue;
            output1 = (allpassFeedback * -1 * inputValue) + circBuf.output() + (allpassFeedback * filterBuf.output());// y[n] = (-g * x[n]) + x[n - d] + (g * y[n - d])
            filterBuf.input(output1);
            std::cout << "          bufOutput: " << filterBuf.output();
            std::cout << "          output: " << output1 << std::endl;
            circBuf.incrementHeads();
            filterBuf.incrementHeads();
            return output1;
        }

        void setAllpass(float gain, double delay)
        {
            this->allpassFeedback = gain;
            this->allpassDelay = delay;
            circBuf.setDistance(allpassDelay, false);
            filterBuf.setDistance(allpassDelay, false);
        }

    private:

        CircBuffer circBuf = { CircBuffer(samplerate) }; //delay buffer for allpass input X[n-d]
        CircBuffer filterBuf = { CircBuffer(samplerate) }; //delay buffer for allpass output (Y[n-d])
    
        float cutoff;
        float resonance;
        int mode { 2 };
        float output1;
        float output2;
        int samplerate;
        float allpassFeedback { 0.2f };
        double allpassDelay { 5.0 };
};