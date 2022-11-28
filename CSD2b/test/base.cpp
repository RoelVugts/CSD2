#include "base.h"

Base::Base() 
{
    std::cout << "Base constructor" << std::endl;
}

void Base::setSound(std::string sound)
{
    this->sound = sound;
}

std::string Base::getSound()
{
    return sound;
}

void Base::play()
{
    std::cout << sound << std::endl;
}