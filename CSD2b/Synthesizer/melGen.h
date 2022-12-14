#pragma once
#include <vector>
#include <thread>

#include "timer.h"
#include "sine.h"
#include "antiAliasedSaw.h"
#include "sawtooth.h"
#include "oscillator.h"
#include "synth.h"


class Melody {
    public:

    Melody();
    
    void addNote(int numNotes, int startNote);
    float getNote(int readPointer);
    int getSize();

    void clear();
    void play(int BPM, Synth* target); //function to call from main
    void playInThread(int BPM, Synth* target); //gets executed in a thread by play()
    void stop(); //joins the thread


    protected:
        std::vector<float> notes;
        Timer timer;
        int readPointer;
        bool playing{false};
        std::thread t;
};