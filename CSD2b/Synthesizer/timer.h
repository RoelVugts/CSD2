#pragma once

#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

class Timer {
    public:
        Timer();
        ~Timer();

    void start();
    void stop();
    double getTime();

    private:
        double startTime;
        double timer;
        bool started{false};
};

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