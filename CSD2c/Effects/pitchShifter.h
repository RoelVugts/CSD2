#include "effect.h"

#include "delay.h"
#include <cmath>

#pragma once

class PitchShifter : public Effect {
    public:

        void prepareToPlay(int sampleRate) override
        {
            delay1.prepareToPlay(sampleRate);
            delay2.prepareToPlay(sampleRate);
            this->sampleRate = sampleRate;
        }

        float output(float input) override
        {
            tick(); //increment the phase of the phasor
            delay1.setDelayTime(window * line1);
            delay2.setDelayTime(window * line2);
            float sum = amp1 * delay1.output(input) + amp2 * delay2.output(input);
            return sum;
        }

        void tick()
        {   
            line1 = line1 + phasorFreq / (float)sampleRate;
            line2 = line2 + phasorFreq / (float)sampleRate;
            wrapRamp(line1);
            wrapRamp(line2);

            // std::cout << "Line1: " << line1 << "     " << "Line2: " << line2 << "    ";
            
            float angle1 = (line1 * 2.0f * pi - pi) / 2.0f;
            float angle2 = (line2 * 2.0f * pi - pi) / 2.0f;

            amp1 = cos(angle1);
            amp2 = cos(angle2);
            // std::cout << "amp1: " << amp1 << "    " << "amp2: " << amp2 << "    " << "sum: " << (amp1 + amp2) << std::endl;
        }

        void setPitch(float pitch)
        {
            phasorFreq = (1.0f - pitch) / (window/1000.0f); // Fout(Hz) = Fin(Hz) * (1 - ( Fp(Hz) * w(s))) --> (1 - (Fout/Fin(Hz))) / w(s) = Fp(Hz)
            std::cout << phasorFreq << std::endl;
        }



        

    private:

        void wrapRamp(float& ramp)
        {
            if (ramp > 1.0f)
                ramp -= 1.0f;
            else if (ramp < 0.0f)
                ramp = 1.0f;
        }



        Delay delay1 = Delay();
        Delay delay2 = Delay();
        float line1 { 0.0f }, line2 { 0.5f }; //line2 at 0.5 --> 180 degrees phase shift
        float pitch = 0.0f;
        float phasorFreq { 0.0f };
        float window { 100.0f };
        int sampleRate;
        float amp1 { 1.0f }, amp2 { 1.0f };
        float pi = acos(-1);


};