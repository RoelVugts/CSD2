
#include <vector>

#pragma once

class Melody {
    public:

    Melody();
    
    void addNote(int numNotes, int minimum, int maximum);
    float getNote(int readPointer);
    int getSize();

    void clear();

    protected:
        std::vector<int> notes;
        float freq;
        int writePointer;
};