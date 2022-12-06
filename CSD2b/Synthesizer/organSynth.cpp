#include "organSynth.h"

#include <iostream>

OrganSynth::OrganSynth()
{
    std::cout << "Constructed OrganSynth" << std::endl;
    squareLow = Square(400, 1.0);
    squareMid = Square(800, 0.5);
    squareLow = Square(1200, 0.2);
}

OrganSynth::~OrganSynth()
{
    std::cout << "OrganSynth Deconstructor" << std::endl;
}

float OrganSynth::getSample()
{
    sample = squareLow.getSample() + squareMid.getSample() + squareHigh.getSample();
    return sample;
}

void OrganSynth::tick()
{
    squareLow.tick();
    squareMid.tick();
    squareHigh.tick();
}
