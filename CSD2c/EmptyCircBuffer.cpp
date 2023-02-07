#include "EmptyCircBuffer.h"

#include <iostream>
#include <unistd.h>
#include <thread>
#include <cmath>

void CircBuffer::input (float value) 
{
    buffer[writeHead] = value;
}

float CircBuffer::output() 
{
    if (readHead > 0)
        return buffer[readHead];
    else
        return 0.0f;
}

void CircBuffer::setDistance (uint distance) 
{   
    if (readHead > distance)
    {
        readHead = currentSize - distance;
    } else
    {
        readHead = currentSize - distance + readHead; //wrap readHead to end if it's in front of writeHead
    }
}

void CircBuffer::goToDistance(uint distance, int time)
{
    int delta = distance - calculateDistance(); //calculate difference between new distance and old distance

    for (int i = 0; i < abs(delta); i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(time));

        if (delta > 0)
            readHead -= 1;
        else
            readHead += 1;
    }
}

void CircBuffer::setDistance(uint distance, int time)
{
    t = std::thread(&CircBuffer::goToDistance, this, distance, time);
}

int CircBuffer::calculateDistance()
{
    if (writeHead < readHead)
        return currentSize - readHead + writeHead;
    else
        return (writeHead - readHead);
}

void CircBuffer::incrementHeads() 
{
    incrementWrite();
    incrementRead();
}

int CircBuffer::getSize() const
{
    return currentSize;
}

int CircBuffer::getReadPosition() const
{
    return readHead;
}

int CircBuffer::getWritePosition() const
{
    return writeHead;
}

inline void CircBuffer::wrapHeader (uint& head) 
{
    if (head >= currentSize)
        head -= currentSize;
    else if (head < 0)
    {
        head = currentSize + head;
    }
}

inline void CircBuffer::incrementWrite() 
{
    writeHead++;
    wrapHeader(writeHead);
}
inline void CircBuffer::incrementRead() 
{
    readHead++;
    wrapHeader(readHead);
}

void CircBuffer::deleteBuffer() 
{
        delete[] buffer;
}

void CircBuffer::setSize(uint size)
{
    float* newBuffer = new float[size];
    std::copy(buffer, buffer+currentSize, newBuffer);

    deleteBuffer();

    buffer = newBuffer;

    if (writeHead < readHead)
        readHead += (size - currentSize); //reset the distance when buffer is resized

    currentSize = size;
}