#include <iostream>
#include "instrument.h"

int main() {
    Instrument snare("Snare");
    snare.playSound("poeffff");

    Instrument piano("Piano");
    piano.playSound("tuuuuuummmmmm");

    snare.roll(19);

}