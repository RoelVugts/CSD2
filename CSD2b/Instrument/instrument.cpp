#include <iostream>
#include "instrument.h"

// Instrument::playSound(std::string soundsLike) {
//     std::cout << "Playing " + Instrument::sound + ": " + soundsLike << std::endl;
// }

void Instrument::roll() {
    for(int i = 0; i < 10; i++) {
        std::cout << "Playing: " + Instrument::sound + ": " << rollSounds[i%5] << std::endl;
    }
}