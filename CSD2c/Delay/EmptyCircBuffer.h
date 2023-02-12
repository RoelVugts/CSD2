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
    void setDistance (uint distance);
    void goToDistance(uint distance, int time);
    void setDistance(uint distance, int time);
    void incrementHeads();
    void setSize(uint size);

    int getSize() const;
    int getReadPosition() const;
    int getWritePosition() const;    
    int getDistance();

// private:
    inline void wrapReadHeader (uint& head);
    inline void wrapWriteHeader (uint& head);
    inline void incrementWrite();
    inline void incrementRead();
    void deleteBuffer();


    float* buffer;
    float* newBuffer;
    float smoothOutput;
    bool delayStarted { false }, waitingForResize { false };
    bool changeDistance { false };
    int distance, newDistance;
    bool changeIncrement { false };

    uint currentSize { 0 }, newSize { 0 }; //newSize is a variable that stores the new bufferSize when the setSize() function is called
    uint writeHead { 0 }, readHead { 0 };
    uint writeMax { 0 }, readMax { 0 }; 
};