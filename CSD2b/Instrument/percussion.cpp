#include "percussion.h"
#include "instrument.h"

#include <iostream>

using namespace std;

Percussion::Percussion() : Percussion(0, 0, 0, 0, "Unknown type")
{

}

Percussion::Percussion(float attackTime, float decayTime, float sustainLevel, float releaseTime, string type) 
: Instrument(attackTime, decayTime, sustainLevel, releaseTime), type(type)
{
    if(type == "Snare") 
    {
        this->sound = "Doemmffff";
    }
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

void Percussion::setType(string type) 
{
    this->type = type;
}

string Percussion::getType() 
{
    return type;
}

void Percussion::setResonance(int resonance)
{
    this->resonance = resonance;
}

int Percussion::getResonance()
{
    return resonance;
}