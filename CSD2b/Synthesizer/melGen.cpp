#include "melGen.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <thread>
#include <algorithm>


Melody::Melody()  //default constructor
{
    readPointer = 0;
}

void Melody::addNote(int numNotes, int startNote) //random melody generation based on probability
{ 

    int aMinor[22] = {45, 47, 48, 50, 52, 53, 55, 57, 59, 60, 62, 64, 65, 67, 69, 71, 72, 74, 76, 77, 79, 81};

    int pitch; //var that selects the element in the aMinor array
    int newNote = 0; //amount that will be added to pitch after each iteration

    if (startNote > aMinor[21]) 
    {
        startNote = 81;
        pitch = 21;
    } else if (startNote < aMinor[0]) {
        startNote = 45;
        pitch = 0;
    } else if (std::find(std::begin(aMinor), std::end(aMinor), startNote) != std::end(aMinor)) {
        //search startNote in array and set pitch to index of the found element
        pitch = std::distance(aMinor, std::find(std::begin(aMinor), std::end(aMinor), startNote));
    } else {
        pitch = 14; //if not found set pitch to midinote 69
    }
    notes.push_back(startNote); //add first note to begin of notes array

    std::srand(clock()); //seeds the random
    
    for(int i = 0; i < numNotes-1; i++)
    {

        int randomNum = rand() % 100; //create randomNum
        int randomNeg = rand() % 100; //create randomNum for going up or down

        if (randomNeg < 50)
        {
            randomNeg = 1;
        } else {
            randomNeg = -1;
        }

        if (randomNum < 70)
        {
            newNote = 2 * randomNeg; //do a minor/major second
        } else if (randomNum > 70 && randomNum < 80)
        {
            newNote = 1 * randomNeg; //do a minor/major third
        } else if (randomNum > 80 && randomNum < 90)
        {
            newNote = 0; //do unisono
        } else if (randomNum > 90 && randomNum < 95)
        {
            newNote = 3 * randomNeg; //do a perfect fourth/diminished fifth
        } else if (randomNum > 95)
        {
            newNote = 4 * randomNeg; //do a perfect fifth/minor sixth
        }

        //check if pitch goes out of range of the aMinor array
        if ((pitch + newNote) > 21 || (pitch + newNote) < 0)
        {
            pitch += (newNote *-1);
        } else {
            pitch += newNote;
        }
        
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
        bool onebang = true;
        int modTimer;
        while (playing) {
            timer.start();
            modTimer = int(timer.getTime()) % int(tempoMS);

            if (modTimer > 0 && modTimer < 50 && onebang) //check if it is in a range because it skipped a note sometimes
            {
                onebang = false; //close gate so notes can't fire rapidly after each other
                std::cout << "Note: " << readPointer + 1 << "   Pitch: " << notes[readPointer] << std::endl;
                target->setPitch(notes[readPointer++]);

                if (readPointer == int(notes.size()))
                {
                    readPointer = 0; //repeat melody
                }
            } else if (modTimer > 50) {
                onebang = true; //Gate for next note is open
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