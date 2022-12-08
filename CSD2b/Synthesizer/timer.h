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