#include <iostream>
#include "instrument.h"


void Instrument::playSound() {
    std::cout << Instrument::sound << std::endl;
}

void Instrument::showHarmonics(int tonic) 
{
    int harmonics[5];
    if(Instrument::harmonic == "Even") 
    {
        harmonics[0] = tonic*1;
        harmonics[1] = tonic*2; 
        harmonics[2] = tonic*3; 
        harmonics[3] = tonic*4;
        harmonics[4] = tonic*5;
    } else if(Instrument::harmonic == "Uneven") 
    {
        harmonics[0] = tonic*1;
        harmonics[1] = tonic*3; 
        harmonics[2] = tonic*5; 
        harmonics[3] = tonic*7;
        harmonics[4] = tonic*9;
    }

    for(int i = 0; i < 5; i++) {
        std::cout << "Harmonics: " << harmonics[i] << std::endl;
    }
}