
#include <iostream>
#include <thread>
#include "env.h"

Envelope::Envelope() : Envelope(5, 50, 0.0, 5)
{

}

Envelope::Envelope(float attack, float decay, float sustain, float release)
: attack(attack), decay(decay), sustain(sustain), release(release)
{

}

void Envelope::setADSR(float attack, float decay, float sustain, float release)
{
    this->attack = attack;
    this->decay = decay;
    this->sustain = sustain;
    this->release = release;
}

void Envelope::triggerInThread()
{
    level = 0.0f;
    envTimer.stop();
    while (triggered) {
        envTimer.start();
        elapsedTime = envTimer.getTime();
        // std::cout << "Time: " << elapsedTime << std::endl;
        if (elapsedTime < attack) {
            level = elapsedTime/attack;
            // std::cout << "Attack" << std::endl;
        }

        if (elapsedTime > attack && elapsedTime < (attack+decay)) {
            level = 1.0f -  ((elapsedTime-attack)/decay)*(1.0f-sustain);
            // std::cout << "Decay" << std::endl;
        }

        if (elapsedTime > (attack+decay) && elapsedTime < (attack+decay+noteOnTime)) {
            level = sustain;
            // std::cout << "sustain" << std::endl;
        }

        if (elapsedTime > (attack+decay+noteOnTime)) {
            level = sustain - ((elapsedTime-attack-decay-noteOnTime)/release)*sustain;
            // std::cout << "Release" << std::endl;
        }
        if (elapsedTime > (attack + decay + noteOnTime + release)) {
            triggered = false;
            elapsedTime = 0;
            envTimer.stop();
        }
        // std::cout << "Level: " << level << std::endl;
    } //while (triggered)
}

float Envelope::getLevel()
{
    return level;
}

void Envelope::trigger()
{   
    triggered = false; //stop current envelope
    if (!triggered) {
        triggered = true;
        std::cout << "realTrigger" << std::endl;
        // t = std::thread(&Envelope::triggerInThread, this);
        // t.join();
        triggerInThread();
    }
}