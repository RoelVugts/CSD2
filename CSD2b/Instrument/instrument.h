#pragma once

#include <iostream>

class Instrument
{
public:
    std::string sound;
    std::string harmonic;

    Instrument(std::string s, std::string h) {
        sound = s;
        harmonic = h;
    }

    void playSound();
    void showHarmonics(int tonic);

    private:
        int harmonics;


};