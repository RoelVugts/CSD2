#include "effect.h"

#include "delay.h"
#include <cmath>

#pragma once

//TRY THIS WITHOUT HEADPHONES SO THE SPEAKER FEEDBACKS WITH THE MIC (+ OR - 12 PITCH)
//GAME SOUND DESING MACHINE

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
            delay1.setDelayTime(window * line1); //continuously change the delay time
            delay2.setDelayTime(window * line2); //also but with 180 degrees phase shift
            float sum = amp1 * delay1.output(input) + amp2 * delay2.output(input);
            return sum;
        }
        
        void setPitch(float pitch)
        {
            float convertedPitch = pow(2.0f, (pitch/12.0f)); //equal temperament
            phasorFreq = (1.0f - convertedPitch) / (window/1000.0f); // Fout(Hz) = Fin(Hz) * (1 - ( Fp(Hz) * w(s))) --> (1 - (Fout/Fin(Hz))) / w(s) = Fp(Hz)
            this->pitch = pitch;
        }

    private:

        void tick()
        {   
            line1 = line1 + phasorFreq / (float)sampleRate; //generate a ramp (sawtooth)
            line2 = line2 + phasorFreq / (float)sampleRate; //same but with 180 degrees phase shift
            wrapRamp(line1);
            wrapRamp(line2);
            
            float angle1 = (line1 * 2.0f * pi - pi) / 2.0f; //map ramp value (0.0 - 1.0) to (-0.5*pi - 0.5*pi)
            float angle2 = (line2 * 2.0f * pi - pi) / 2.0f;

            //2 cosine waves that are 0 at the moment the delay time is reset, this is to avoid clicks in the audio
            amp1 = cos(angle1);
            amp2 = cos(angle2);
        }

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
        float window { 100.0f }; //delay window
        float amp1 { 1.0f }, amp2 { 1.0f };

        int sampleRate;
        float pi = acos(-1);


};