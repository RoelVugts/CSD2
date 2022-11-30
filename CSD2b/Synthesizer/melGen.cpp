#include "melGen.h"
#include <iostream>

#include <math.h>

Melody::Melody()  //default constructor
{
    writePointer = 0;

    for(int i = 0; i < NUM_NOTES; i++) 
    {
        notes[i] = -1; //fill note array with -1
    }
}

void Melody::addNote(int midiNote)
{
    freq = 440 * pow(2, (midiNote - 69)/12.0f); //convert midiNote to Frequency
    notes[writePointer++] = freq;
}

float Melody::getNote(int readPointer)
{   
    if (notes[readPointer] == -1)
    {
        std::cout << "Note is empty" << std::endl;
    } else {
        return notes[readPointer];
    }
}