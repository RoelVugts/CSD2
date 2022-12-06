#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <thread>

#include "timer.h"
using namespace std;

bool running = true;
int readPointer = 0;
Timer timer1;
vector<int> notes; 

void countNotes()
{
    timer1.start();
    while (running) {
        if (fmod(timer1.getTime(), 500) == 0) {
            cout << "Time: " << timer1.getTime() << endl;
            cout << "Note: " << notes[readPointer++] << endl;
            if (readPointer >= int(notes.size()))
            {
                readPointer = 0;
            }
        }
    }
}


int main() 
{

    for(int i = 0; i <= 7; i++)
    {
        notes.push_back(i);
    }


    thread worker(countNotes);
    auto input = cin.get();

    if (input != 0) {
        running = true;
    } else {
        running = false;
    }

    worker.join();



    cout << "Vector length: " << notes.size() << endl;



    return 0;
}