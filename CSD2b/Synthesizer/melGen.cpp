#include "melGen.h"
#include <iostream>
#include <cstdlib>

#include <math.h>

using namespace std;

Melody::Melody()  //default constructor
{
    writePointer = 0;
}

void Melody::addNote(int numNotes, int minimum, int maximum)
{
     int range = maximum - minimum;   


    for(int i = 0; i < numNotes; i++)
    {
        srand(i);
        int randomNote = (rand() % range) + minimum;
        freq = 440 * pow(2, (randomNote - 69)/12.0f); //convert midiNote to Frequency
        notes.push_back(freq);
        // cout << "Added: " << notes[i] << endl;
    }
}

float Melody::getNote(int readPointer)
{   
    if (notes[readPointer] == -1)
    {
        cout << "Note is empty" << endl;
    } else {
        return notes[readPointer];
    }
}

int Melody::getSize()
{
    return notes.size();
}

void Melody::clear() 
{
    notes.clear();
}