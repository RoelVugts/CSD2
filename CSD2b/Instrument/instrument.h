#pragma once

#include <iostream>

class Instrument {
    public:
        std::string sound;
        std::string rollSounds[5] = {"Boem", "baduum", "poefff", "katsss", "trrrr"};
        //playSound();
        void roll();
    Instrument(std::string objectSound) {
        sound = objectSound;
    };
};