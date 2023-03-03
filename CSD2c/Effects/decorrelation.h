#include "filter.h"
#include "effect.h"

#pragma once

#include <vector>

class Decorrelator : public Effect {
    public:
        Decorrelator() {};
        ~Decorrelator() {};

        virtual void prepareToPlay(int sampleRate) override
        {
            this->sampleRate = sampleRate;
            // setFilterAmount(5);
            for (Filter& filter : filters)
            {
                    filter.prepareToPlay(sampleRate);
            }
            filters[0].setAllpass(0.8f, 78);
            filters[1].setAllpass(0.99f, 358);
            filters[2].setAllpass(0.9f, 20.73);
            filters[3].setAllpass(0.9f, 930);
            filters[4].setAllpass(0.75f, 149.6);
        }

        virtual float output(float input) override
        {
            float output = input;
            
            for (Filter& filter : filters)
                output = filter.output(output);
            
            return output;
        }

        void setCorrelation(float correlation)
        {
            this->correlation = correlation;
        }

        void setFilterAmount(uint amount)
        {
            // this->filterAmount = amount;
            // for (uint i  = 0; i < amount; i++)
            //     filters.push_back(Filter());
        }

        void setCoefficients()
        {  
            // std::vector<Filter*>::iterator i = filters.begin();
            // while (i != filters.end())
            // {
            //         (*i)->prepareToPlay(sampleRate);
            //         (*i)->setAllpass(0.8f, 12.0);
            //         i++;
            // }
        }  



    private:
        float correlation;
        Filter filters[5] { Filter(), Filter(), Filter(), Filter(), Filter() };
        uint filterAmount;
        int sampleRate;
};