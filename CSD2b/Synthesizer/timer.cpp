#include "timer.h"

#include <iostream>

Timer::Timer()
{

}

Timer::~Timer()
{
    cout << "Timer terminated" << endl;
}


void Timer::start()
{
    if (!started)
    {
        startTime = clock(); //set startTime
        started = true;
    } else
    {
        timer = (clock() - startTime) / 1000; //running the timer
    }
}

double Timer::getTime()
{
    return timer;
}

void Timer::stop()
{   
    if (started)
    {
        started = false;
    }

}