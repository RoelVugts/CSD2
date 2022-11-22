#include <iostream>
#include <cmath>
#include <unistd.h>

#include "instrument.h"
#include "percussion.h"
#include "synth.h"

using namespace std;

int main() {

    Percussion snare(5,6,7,8, "Snare");

    snare.setName("Dirty Snare");
    snare.setHarmStruct("Noisy");
    snare.setSound("Duummffff");
    cout << "\n";

    snare.hit();

    Synth osc;
    osc.setOscillator("Square");

    osc.setFreq(200);
    
    cout << "\n";
    for(float i = 1; i < 20; i++) {
        cout << osc.play(i) << endl;
        usleep(100000); // 1/44100
    };



    return 0;
}