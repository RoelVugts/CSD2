//
// Created by Dean on 05/02/2023.
//

#include <iostream>
#include <thread>

#pragma once

class CircBuffer {
    using uint = unsigned int;

public:
    CircBuffer (uint size) : currentSize (size), buffer (new float[currentSize]) {  }
    ~CircBuffer() { deleteBuffer(); std::cout << "buffer deleted" << std::endl; }

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
    std::thread t;

private:
    inline void wrapHeader (uint& head);
    inline void incrementWrite();
    inline void incrementRead();
    void deleteBuffer();
    int calculateDistance();

    float* buffer;
    float smoothOutput;
    uint currentSize { 0 };
    uint writeHead { 0 }, readHead { 0 };
};