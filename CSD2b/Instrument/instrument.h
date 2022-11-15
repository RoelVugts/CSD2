#include <iostream>

class Instrument {
    public:
        std::string sound;
    Instrument(std::string objectSound) {
        sound = objectSound;
    }
    
    void playSound(std::string soundsLike) {
        std::cout << "Playing " + sound + ": " + soundsLike << std::endl;
    }
};