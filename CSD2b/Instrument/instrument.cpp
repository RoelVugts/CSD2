#include <iostream>
#include "instrument.h"


//Constructors and Deconstructors
//-----------------------------------------------------------

Instrument::Instrument() : Instrument(0, 0, 0, 0)  //default constructor
{ 
    // cout << "Attack time set to default: " << attackTime << endl;
    // cout << "Decay time set to default: " << decayTime << endl;
    // cout << "Sustain level set to default: " << sustainLevel << endl;
    // cout << "Release time set to default: " << releaseTime << endl;
}

Instrument::Instrument(float attackTime, float decayTime, float sustainLevel, float releaseTime) //constructor
: attackTime(attackTime), decayTime(decayTime), sustainLevel(sustainLevel), releaseTime(releaseTime)
{

}

Instrument::~Instrument() //deconstructor
{ 

}

//Getters and Setters
//------------------------------------------------------------

void Instrument::setName(string name) {
    this->name = name;
}

string Instrument::getName() {
    return name;
}

void Instrument::setHarmStruct(string harmStruct) {
    this->harmStruct = harmStruct;
}

string Instrument::getHarmStruct() {
    return harmStruct;
}

void Instrument::setSound(string sound) {
    this->sound = sound;
}

string Instrument::getSound() {
    return sound;
}

void Instrument::setAttackTime(float attackTime) {
    this->attackTime  = attackTime;
}

float Instrument::getAttackTime() {
    return attackTime;
}

void Instrument::setDecayTime(float decayTime) {
    this->decayTime  = decayTime;
}

float Instrument::getDecayTime() {
    return decayTime;
}

void Instrument::setSustainLevel(float sustainLevel) {
    this->sustainLevel  = sustainLevel;
}

float Instrument::getSustainLevel() {
    return sustainLevel;
}

void Instrument::setReleaseTime(float releaseTime) {
    this->releaseTime  = releaseTime;
}

float Instrument::getReleaseTime() {
    return releaseTime;
}

//Member functions
//------------------------------------------------------------


void Instrument::play() {
    std::cout << Instrument::sound << std::endl;
}
