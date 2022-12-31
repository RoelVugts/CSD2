#include "timer.h"

#include <iostream>
#include <chrono>

Timer::Timer()
{

}

Timer::~Timer()
{
    std::cout << "Timer terminated" << std::endl;
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

float Timer::getTime()
{
    return timer;
}

void Timer::stop()
{   
    if (started)
    {
        started = false;
        timer = 0;
    }

}