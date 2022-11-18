#include <iostream>

#include "instrument.h"

int main() {
    Instrument snare("kadoef", "Uneven");
    snare.playSound();
    snare.showHarmonics(100);
    return 0;
}