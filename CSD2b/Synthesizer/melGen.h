#pragma once
#include <vector>

#include "timer.h"
#include "sine.h"
#include "antiAliasedSaw.h"
#include "sawtooth.h"


class Melody {
    public:

    Melody();
    
    void addNote(int numNotes);
    float getNote(int readPointer);
    int getSize();

    void clear();
    void play(int BPM, Sawtooth& target);

    Timer timer;

    protected:
        std::vector<float> notes;
        float freq;
        int writePointer;
        int readPointer;
};