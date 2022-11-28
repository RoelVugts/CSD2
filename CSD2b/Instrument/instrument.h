#pragma once

#include <iostream>

using namespace std;

class Instrument
{
public:
    Instrument();
    Instrument(float attackTime, float decayTime, float sustainLevel, float releaseTime);
    ~Instrument();

    //---------------------------------------

    void setName(string name);
    string getName();

    virtual void setSound(string sound);
    string getSound();
    
    void setHarmStruct(string harmStruct);
    string getHarmStruct();

    void setAttackTime(float attackTime);
    float getAttackTime();

    void setDecayTime(float decayTime);
    float getDecayTime();

    void setSustainLevel(float sustainLevel);
    float getSustainLevel();

    void setReleaseTime(float releaseTime);
    float getReleaseTime();
    
    //----------------------------

    virtual void play();

protected:
    string name;
    string harmStruct;
    float attackTime;
    float decayTime;
    float sustainLevel;
    float releaseTime;
    string sound;

};