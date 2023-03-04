#include "filter.h"
#include "effect.h"
#include "Util.h"

#pragma once

#include <vector>

class Decorrelator : public Effect {
    public:
        Decorrelator() {};
        ~Decorrelator() {};

        virtual void prepareToPlay(int sampleRate) override
        {
            this->sampleRate = sampleRate;

            for (Filter& filter : filters)
            {
                    filter.prepareToPlay(sampleRate);
            }
            setCoefficients();
        }

        virtual float output(float input) override
        {
            float output = input;
            
            for (Filter& filter : filters)
                output = filter.output(output);
            
            return (1.0f - dryWet) * input + dryWet * output;
        }

        void setCoefficients()
        {  
            for (Filter& filter : filters)
            {
                float gain = Util::random(1000) / 1000.0f;
                float delay = Util::random(sampleRate/2);
                std::cout << "Gain: " << gain;
                std::cout << "        Delay: " << delay << std::endl;
                filter.setAllpass(gain, delay);
            }
        }  



    private:
        float correlation;
        Filter filters[512] { {Filter()} };
        uint filterAmount;
        int sampleRate;
};