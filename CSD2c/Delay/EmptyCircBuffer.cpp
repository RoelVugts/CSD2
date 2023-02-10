#include "EmptyCircBuffer.h"

#include <iostream>
#include <unistd.h>
#include <thread>
#include <cmath>



CircBuffer::CircBuffer(uint size) : currentSize (size), buffer (new float[currentSize]), newBuffer(nullptr)
{ 
    oldSize = size;
    writeMax = size; readMax = size;

}

CircBuffer::~CircBuffer()
{
    delete[] buffer; 
    std::cout << "buffer deleted" << std::endl;
}


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
    if (distance < currentSize) //if the new distance is greater than the buffer size
        this->distance = distance;
    else
        this->distance = currentSize - 1;


    if (!delayStarted)
        readHead = 0;
    else 
    {
        if (writeHead > this->distance) //if true then the writehead is in front of the readhead in the buffer
        {
        readHead = writeHead - this->distance;
        } 
        else
        {
        readHead = currentSize - this->distance + writeHead; //wrap readHead to end if it's in front of writeHead
        
        }
    }
    // std::cout << "Distance: " << this->distance << std::endl;
    // std::cout << "readHead: " << getReadPosition() << std::endl;
    // std::cout << "writeHead: " << getWritePosition() << std::endl;
}

void CircBuffer::goToDistance(uint distance, int time)
{
    int delta = distance - calculateDistance(); //calculate difference between new distance and old distance
    std::cout << "changing delay time" << std::endl;
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
    t.join();
    std::cout << "Reached new delay time" << std::endl;
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
        readMax = currentSize; //if buffer is resized when readHead is > writeHead then it wraps the readHead based on the old buffer size

    if (head >= readMax)
        head -= readMax;

    // std::cout << "CurrentSize: " << currentSize << std::endl;
    // std::cout << "OldSize: " << oldSize << std::endl;
    // std::cout << "ReadHead: " << readHead << std::endl;
}

inline void CircBuffer::wrapWriteHeader(uint& head)
{
    if (head >= writeMax)
        head -= writeMax;
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

    if (waitingForResize)
    {
        if (readHead <= writeHead)
        {
            delete[] buffer;
            buffer = newBuffer;
            waitingForResize = false;
            currentSize = newSize;
            readMax = currentSize;
        }
    }
}

void CircBuffer::deleteBuffer() 
{
        delete[] buffer;
}

void CircBuffer::setSize(uint size)
{
    //----------------------------------------------------------------
    //when new size equals old size
    if (size == currentSize)
        return; //exit function
    
    //----------------------------------------------------------------
    //when new size is bigger than old size
    newBuffer = new float[size];
    
    if (size > currentSize)
    {
        std::copy(buffer, buffer+currentSize, newBuffer);
        delete[] buffer;
        buffer = newBuffer;
        currentSize = size;
        writeMax = size;
    }
    else 
        std::copy(buffer, buffer+size, newBuffer);

    //----------------------------------------------------------------
    //when new size is smaller than new size
    if (size < currentSize)
    {
        if (distance > size)
        {
            setDistance(size-1); //decrease delay time when new bufferSize is smaller than the current delay time
        }

        if (writeHead > size && readHead < size || writeHead > size && readHead > size)
        {
            std::cout << "Writehead larger than newbufSize and/or readhead larger" << std::endl;
            std::copy(buffer, buffer+size, newBuffer);
            writeMax = writeHead+1;
            readMax = writeMax;
            waitingForResize = true;
            newSize = size;
        } else if (readHead > size && writeHead < size)
        {
            std::cout << "readhead larger than newbufSize and writehead smaller" << std::endl;
            std::copy(buffer, buffer+size, newBuffer);
            // delete[] buffer;
            waitingForResize = true;
            writeMax = size;
            
        } else if (readHead < size && writeHead < size)
        {
            std::cout << "readHead and writehead both smaller" << std::endl;
            std::copy(buffer, buffer+size, newBuffer);
            writeMax = size;
            readMax = size;
            delete[] buffer;
            buffer = newBuffer;
            currentSize = size; 
        }
    }



    
    //TODO: Also check what to do when the new size is smaller than the distance --> change distance to new size-1 and then wait until write and read pointer are in the new small buffer and then resize
}