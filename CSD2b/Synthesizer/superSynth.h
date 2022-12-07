#include "synth.h"
#include "oscillator.h"

class SuperSynth : virtual public Oscillator, Synth {
    public:
        SuperSynth();
        ~SuperSynth();
    
    protected:
        float detune;
        int voices;
        float phase2, phase3, phase4, phase5;
        void calculate();

};