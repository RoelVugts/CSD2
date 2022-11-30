#include "oscillator.h"

class Sawtooth : public Oscillator {
    public:
        Sawtooth();
        Sawtooth(float frequency, float amplitude, float phase, float samplerate);
        Sawtooth(float frequency, float amplitude);
        ~Sawtooth();
    
    void process();
};