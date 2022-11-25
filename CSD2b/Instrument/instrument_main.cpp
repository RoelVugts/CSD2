#include <iostream>
#include <unistd.h>
#include <math.h>
#include "instrument.h"
#include "percussion.h"
#include "synth.h" 
#include "sampler.h"
#include "perc_synth.h"

using namespace std;

int main() {

    Percussion snare(5,6,7,8, "Snare");

    snare.setName("Dirty Snare");
    snare.setHarmStruct("Noisy");
    cout << "\n";
    snare.play();

    Synth osc(10, 5, 1, 15, "Sine", 400, 1.0, 0);
    osc.play();

    Sampler tomSample(1, 50, 1, 10, "lowTom");
    tomSample.play();

    PercSynth synthKick;
    synthKick.Percussion::setSound("Boem");
    synthKick.Percussion::play();

    cout << "\n" << endl;

    return 0;

}