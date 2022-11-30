#define NUM_NOTES 13

#pragma once

class Melody {
    public:

    Melody();
    
    void addNote(int midiNote);
    float getNote(int readPointer);

    protected:
        int notes[NUM_NOTES];
        float freq;
        int writePointer;
};