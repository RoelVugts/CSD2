#include "melGen.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>

using namespace std;

Melody::Melody()  //default constructor
{
    writePointer = 0;
    readPointer = 0;
}

void Melody::addNote(int numNotes)
{
    int range = 8;   
    srand(clock());
    int aMinor[8] = {57, 59, 60, 62, 64, 65, 67, 69};

    for(int i = 0; i < numNotes; i++)
    {

        int randomNote = (rand() % range);
        freq = 440.0f * pow(2, (aMinor[randomNote] - 69)/12.0f); //convert midiNote to Frequency
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
    return int(notes.size());
}

void Melody::clear() 
{
    notes.clear();
}



void Melody::play(int BPM, Sawtooth& target) {
    float tempoMS = 60000.0f / BPM; //calculate tempo in MS
    timer.start();
    // std::cout << "melTimer: " << timer.getTime() << std::endl;
    if (fmod(timer.getTime(), tempoMS) == 0)
    {
        std::cout << "Freq: " << notes[readPointer] << std::endl;
        target.setFrequency(notes[readPointer++]);

      if (readPointer == int(notes.size()))
      {
        readPointer = 0;
      }
  }
}
