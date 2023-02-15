//
// Created by Dean on 05/02/2023.
//

#include <iostream>
#include <thread>

#pragma once

class CircBuffer {
    using uint = unsigned int;
public:
    CircBuffer (uint size);
    ~CircBuffer();

    void input (float value);
    float output();
    void setDistance (double distance);
    void setDistance(double distance, int time);
    void incrementHeads();
    void setSize(uint size);

    int getSize() const;
    double getReadPosition() const;
    double getWritePosition() const;    
    double getDistance();

// private:
    inline void wrapReadHeader (double& head);
    inline int readBuffer(double head);
    inline void wrapWriteHeader (uint& head);
    inline void incrementWrite();
    inline void incrementRead();
    void deleteBuffer();


    float* buffer;
    float* newBuffer;
    bool delayStarted { false }, waitingForResize { false };
    bool changeDistance { false };
    bool changeIncrement { false };

    double readIncrement { 1.0 };
    double distance, newDistance;
    uint currentSize { 0 }, newSize { 0 }; //newSize is a variable that stores the new bufferSize when the setSize() function is called
    uint writeHead { 0 };
    double readHead { 0.0 };
    uint writeMax { 0 };
    double readMax { 0.0 };

};