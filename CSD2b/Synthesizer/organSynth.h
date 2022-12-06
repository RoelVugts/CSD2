
#include "synth.h"

class OrganSynth : public Synth {
    public:
        OrganSynth();
        ~OrganSynth();

    Square squareLow;
    Square squareMid;
    Square squareHigh;

    float getSample();
    void tick();

    protected:
        float sample = 0.0f;

};