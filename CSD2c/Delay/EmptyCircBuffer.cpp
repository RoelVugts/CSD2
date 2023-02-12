#include "EmptyCircBuffer.h"

#include <iostream>
#include <unistd.h>
#include <thread>
#include <cmath>


//Constructor
CircBuffer::CircBuffer(uint size) : currentSize (size), buffer (new float[currentSize]), newBuffer(nullptr)
{ 
    writeMax = size; 
    readMax = size;

}

//Destructor
CircBuffer::~CircBuffer()
{
    delete[] buffer; 
    std::cout << "buffer deleted" << std::endl;
}

//Writes to the buffer
void CircBuffer::input (float value) 
{
    buffer[writeHead] = value;
}

//Reads from the buffer
float CircBuffer::output() 
{
    if (readHead > 0)
        return buffer[readHead];
    else
        return 0.0f;
}


//Setters
//----------------------------------------------------------------------


//Sets the delay instantly
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
}

//Sets the delay gradually
void CircBuffer::setDistance(uint distance, int time)
{
    newDistance = distance;
    changeDistance = true;
    std::cout << "Reached new delay time" << std::endl;
}

//Returns the current delay time in samples
int CircBuffer::getDistance()
{
    if (writeHead < readHead)
        return currentSize - readHead + writeHead;
    else
        return (writeHead - readHead);
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
            std::copy(buffer, buffer+size, newBuffer);
            readMax = writeHead;
            writeHead = 0;
            writeMax = size;
            waitingForResize = true;
            newSize = size;
        } 
        else if (readHead > size && writeHead < size)
        {
            std::copy(buffer, buffer+size, newBuffer);
            waitingForResize = true;
            writeMax = size;
            newSize = size;
        } 
        else if (readHead < size && writeHead < size)
        {
            std::copy(buffer, buffer+size, newBuffer);
            writeMax = size;
            readMax = size;
            delete[] buffer;
            buffer = newBuffer;
            currentSize = size;
            newSize = size;
        }
    }
}

//---------------------------------------------------------------------------------

//Increments the heads 1 position further
void CircBuffer::incrementHeads() 
{
    incrementWrite();
    incrementRead();

    if (changeDistance)
    {
        int increment = 1;

        if (changeIncrement)
        {
            increment = 2;
            changeIncrement = false;
            std::cout << "Increment: " << increment << std::endl;
        }
        else if (!changeIncrement)
        {
            increment = 1;
            changeIncrement = true;
        }
        

        if (distance < newDistance) //if new distance is larger than old distance
            setDistance(distance+increment);
        else if (distance > newDistance)
            setDistance(distance-1);
        else
            changeDistance = false;
    }
}

void CircBuffer::deleteBuffer() 
{
        delete[] buffer;
}



//Private functions
//--------------------------------------------------------------------------------
inline void CircBuffer::wrapReadHeader (uint& head) 
{
    if (head <= writeHead) 
        readMax = currentSize; //if buffer is resized (larger than old buf) when readHead is > writeHead then it wraps the readHead based on the old buffer size

    if (head >= readMax)
        head -= readMax;
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
        // if (changeDistance && newDistance < distance)
        readHead++;
        // std::cout << "ReadHead: " << readHead << std::endl;
        wrapReadHeader(readHead);
    }

    if (waitingForResize)
    {
        if (readHead <= writeHead)
        {
            delete[] buffer;
            buffer = newBuffer;
            waitingForResize = false;
            readMax = newSize;
            writeMax = newSize;
            currentSize = newSize;
        }
    }
}


