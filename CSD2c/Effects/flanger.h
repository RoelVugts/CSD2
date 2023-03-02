#include "effect.h"
#include "delay.h"
#include "sine.h"
#include "sawtooth.h"
#include "triangle.h"

class Flanger : public Effect {
    public:
        virtual void prepareToPlay(int samplerate) override
        {
            this->samplerate = samplerate;
            delay.prepareToPlay(samplerate);
            setDepth(depth);
            delay.setDelayTime(depth);
            triangle.setSamplerate(samplerate);
            modTriangle.setSamplerate(samplerate);
        }

        virtual float output(float input) override
        {
            tick();
            // std::cout << "Delay: " << delay.getDelayTime() << std::endl;
            return (1.0f - dryWet) * input + dryWet * delay.output(input);
        }

        void setDepth(float depth)
        {
            this->depth = depth;
            delay.setMaxDelay(depth);
        }

        void setFeedback(float feedback)
        {
            this->feedback = feedback;
            delay.setFeedback(feedback);
        }

    private:
        Delay delay = { Delay() };
        Triangle triangle = { Triangle(0.5f, 0.8f) };
        Triangle modTriangle = { Triangle(0.5f, 0.8f) };
        float depth { 2.0f };
        float freq { 1.0f };
        int samplerate;
        float feedback { 0.0f };

        void tick()
        {
            triangle.tick();
            modTriangle.tick();
            float modSignal = (modTriangle.getSample() + 1) / 2;
            triangle.setFrequency(freq * modSignal);
            float modModSignal = (triangle.getSample() +1) / 2;
            delay.setDelayTime(depth * modModSignal);
        }

        void foldSaw(Sawtooth osc)
        {
            
        }
};



//min delay = 0.0 ms
//max delay = 2- 7 ms