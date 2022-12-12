#pragma once
#include <vector>
#include <thread>

#include "timer.h"
#include "sine.h"
#include "antiAliasedSaw.h"
#include "sawtooth.h"
#include "oscillator.h"


class Melody {
    public:

    Melody();
    
    void addNote(int numNotes);
    float getNote(int readPointer);
    int getSize();

    void clear();
    void play(int BPM, Oscillator* target); //function to call from main
    void playInThread(int BPM, Oscillator* target); //gets executed in a thread by play()
    void stop(); //joins the thread


    protected:
        std::vector<float> notes;
        Timer timer;
        int readPointer;
        bool playing{false};
        std::thread t;
};