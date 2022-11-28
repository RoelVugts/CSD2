#pragma once

#include <iostream>

class Base {
    public:
        Base();

        virtual void setSound(std::string sound);
        std::string getSound();

        virtual void play();

    protected:
        std::string sound;
};