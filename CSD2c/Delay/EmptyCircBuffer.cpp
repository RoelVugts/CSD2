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
    this->distance = distance;

    if (!delayStarted)
        readHead = 0;
    else 
    {
        if (writeHead > distance)
        {
        readHead = writeHead - distance;
        } 
        else
        {
        readHead = currentSize - distance + writeHead; //wrap readHead to end if it's in front of writeHead
        // std::cout << "Readhead after distance: " << readHead << std::endl;
        }
    }
}

void CircBuffer::goToDistance(uint distance, int time)
{
    int delta = distance - calculateDistance(); //calculate difference between new distance and old distance

    for (int i = 0; i < abs(delta); i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(time));

        if (delta > 0)
        {
            readHead -= 1;
            wrapReadHeader(readHead);
        }
        else
            incrementRead();
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

inline void CircBuffer::wrapReadHeader (uint& head) 
{
    if (head <= writeHead) 
        oldSize = currentSize; //if buffer is resized when readHead is > writeHead then it wraps the readHead based on the old buffer size

    if (head >= oldSize)
        head -= oldSize;

    // std::cout << "CurrentSize: " << currentSize << std::endl;
    // std::cout << "OldSize: " << oldSize << std::endl;
    // std::cout << "ReadHead: " << readHead << std::endl;
}

inline void CircBuffer::wrapWriteHeader(uint& head)
{
    if (head >= currentSize)
        head -= currentSize;
    else if (head < 0)
        head = currentSize + head;
}

inline void CircBuffer::incrementWrite() 
{
    writeHead++;
    wrapWriteHeader(writeHead);

    if (writeHead > distance)
        delayStarted = true; //start reading after distance (delay) had been reached
}
inline void CircBuffer::incrementRead() 
{
    if (delayStarted)
    {
        readHead++;
        wrapReadHeader(readHead);
    }
}

void CircBuffer::deleteBuffer() 
{
        delete[] buffer;
}

void CircBuffer::setSize(uint size)
{

    if (size == currentSize)
        return; //exit function
    
    float* newBuffer = new float[size];
    
    if (size > currentSize)
    {
        std::copy(buffer, buffer+currentSize, newBuffer);
    } 
    else 
    {
        std::copy(buffer, buffer+size, newBuffer);
    }

    deleteBuffer();

    buffer = newBuffer;

    currentSize = size;
    
    //TODO: Also check what to do when the new size is smaller than the distance --> change distance to new size-1 and then wait until write and read pointer are in the new small buffer and then resize
}