#include "percussion.h"
#include "instrument.h"

#include <iostream>

using namespace std;

Percussion::Percussion() : Percussion(0, 0, 0, 0, "Unknown type")
{
    cout << "Percussion constructor";
}

Percussion::Percussion(float attackTime, float decayTime, float sustainLevel, float releaseTime, string type) : Instrument(attackTime, decayTime, sustainLevel, releaseTime)
{
    this->attackTime = attackTime;
    this->decayTime = decayTime;
    this->sustainLevel = sustainLevel;
    this->releaseTime = releaseTime;
    this->type = type;
}

void Percussion::showProperties() 
{

    cout << "Name: " << name << endl;
    cout << "Harmonic structure: " << harmStruct << endl;
    cout << "Sound: " << sound << endl;
    cout << "Attack time: " << attackTime << endl;
    cout << "Decay time: " << decayTime << endl;
    cout << "Sustain level: " << sustainLevel << endl;
    cout << "Release time: " << releaseTime << endl; 
    cout << "Type: " << type << endl;
}

void Percussion::hit() {
    cout << name << ": " << sound << endl;
}