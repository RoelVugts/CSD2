#include "pitchShifter.h"
#include "effect.h"

class Doppler : public Effect {
    public:
        virtual void prepareToPlay(int samplerate) override
        {
            this->samplerate = samplerate;
            pitchShifter.prepareToPlay(samplerate);
        }

        virtual float output(float input) override
        {
            float pitch = soundSpeed / (soundSpeed + sourceSpeed); //doppler FREQout = FREQin * (V / (V + Vs))
            pitchShifter.setPitch(pitch);
            return (1.0f - dryWet) * input + dryWet * pitchShifter.output(input);
        }

        void setSourceSpeed(float sourceSpeed)
        {
            this->sourceSpeed = sourceSpeed;
        }
    

    private:
        PitchShifter pitchShifter;
        int samplerate;
        float sourceSpeed { 0.0f };
        float soundSpeed {343.0f};


};