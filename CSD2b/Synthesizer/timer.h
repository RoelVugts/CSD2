#pragma once

#include <iostream>
#include <ctime>
#include <cmath>
#include <chrono>

class Timer {
    public:
        Timer();
        ~Timer();

    void start();
    void stop();
    float getTime();

    private:
        float startTime;
        float timer;
        bool started{false};
};