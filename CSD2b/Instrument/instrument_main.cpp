#include <iostream>
#include <unistd.h>
#include <math.h>
#include "instrument.h"
#include "percussion.h"
#include "synth.h"

using namespace std;

int main() {

    Percussion snare(5,6,7,8, "Snare");

    snare.setName("Dirty Snare");
    snare.setHarmStruct("Noisy");
    cout << "\n";

    snare.play();

    Synth osc(10, 5, 1, 15, "Saw", 400, 1.0, 0);
    osc.play();

    cout << "\n" << endl;
    return 0;
}