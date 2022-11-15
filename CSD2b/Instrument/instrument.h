#include <iostream>

class Instrument {
    public:
        std::string sound;
        std::string rollSounds[5] = {"Boem", "baduum", "poefff", "katsss", "trrrr"};
    Instrument(std::string objectSound) {
        sound = objectSound;
    }
    
    void playSound(std::string soundsLike) {
        std::cout << "Playing " + sound + ": " + soundsLike << std::endl;
    }

    void roll(int numRepetitions) {
        for(int i = 0; i < numRepetitions; i++) {
            std::cout << "Playing: " + sound + ": " << rollSounds[i%5] << std::endl;
        }
    }

};