#include "melGen.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <thread>

using namespace std;

Melody::Melody()  //default constructor
{
    readPointer = 0;
}

void Melody::addNote(int numNotes) //random melody generation based on probability
{ 
    int newNote = 0;
    int pitch = 8;
    // float freq;

    int aMinor[22] = {45, 47, 48, 50, 52, 53, 55, 57, 59, 60, 62, 64, 65, 67, 69, 71, 72, 74, 76, 77, 79, 81};
        srand(clock()); //seeds the random
    
    for(int i = 0; i < numNotes; i++)
    {

        int randomNum = rand() % 100;
        int randomNeg = rand() % 100;
        if (randomNeg < 50)
        {
            randomNeg = 1;
        } else {
            randomNeg = -1;
        }

        if (randomNum < 70)
        {
            newNote = 2;
            pitch += (newNote * randomNeg);
        } else if (randomNum > 70 && randomNum < 80)
        {
            newNote = 1;
            pitch += (newNote * randomNeg);
        } else if (randomNum > 80 && randomNum < 90)
        {
            newNote = 0;
            pitch += newNote;
        } else if (randomNum > 90)
        {
            newNote = 3;
            pitch += (newNote * randomNeg);
        }

        if (pitch < 0)
        {
            pitch *= -1;
        }

        if (pitch > 21)
        {
            pitch += (newNote *-1);
        }

        std::cout << "Note: " << newNote << std::endl;
        std::cout << "random: " << randomNum << std::endl;
        std::cout << "randomNeg: " << randomNeg << std::endl;
        std::cout << "\n" << std::endl;
        notes.push_back(aMinor[pitch]);
    }
}

float Melody::getNote(int readPointer)
{   
    if (notes[readPointer] == -1)
    {
        cout << "Note is empty" << endl;
        return -1;
    } else {
        return notes[readPointer];
    }
}

int Melody::getSize()
{
    return int(notes.size());
}

void Melody::clear() 
{
    notes.clear();
}

void Melody::playInThread(int BPM, Synth* target) { //function that actually plays the melody

        float tempoMS = 60000.0f / BPM; //calculate tempo in MS
        while (playing)
        {
            timer.start();
            if (fmod(timer.getTime(), tempoMS) == 0)
            {
                std::cout << "Note: " << readPointer + 1 << "   Pitch: " << notes[readPointer] << std::endl;
                target->setPitch(notes[readPointer++]);

                if (readPointer == int(notes.size()))
                {
                    readPointer = 0; //repeat melody
                }
            }
        }
    
}

void Melody::play(int BPM, Synth* target) //function that plays the melody in a thread
{
    playing = true;

    t = std::thread(&Melody::playInThread, this, BPM, target);
}

void Melody::stop()
{
    playing = false;
    t.join();
}