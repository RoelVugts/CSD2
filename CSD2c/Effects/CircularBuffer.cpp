#include "CircularBuffer.h"
#include "Util.h"

#include <iostream>
#include <unistd.h>
#include <thread>
#include <cmath>


//Constructor
CircBuffer::CircBuffer(uint size) : buffer (new float[size]), currentSize (size), newBuffer(nullptr)
{ 
    //initialize write- and readHeader wrap values to buffer size
    writeMax = size; 
    readMax = size;

    for (uint i = 0; i < size; i++)
        buffer[i] = 0.0f;

}

//Destructor
CircBuffer::~CircBuffer()
{
    delete[] buffer; 
    std::cout << "buffer deleted" << std::endl;
}


//changes the size of the buffer
void CircBuffer::setSize(uint size)
{
    //----------------------------------------------------------------
    //when new size equals old size
    if (size == currentSize)
        return; //exit function
    
    //----------------------------------------------------------------
    //when new size is bigger than old size
    newBuffer = new float[size]; //create new buffer
    
    if (size > currentSize)
    {
        std::copy(buffer, buffer+currentSize, newBuffer); //copy contents of old buf to new buf
        delete[] buffer; //delete old buf
        buffer = newBuffer; //set new buffer to the buffer we will be using
        currentSize = size; //adjust size 
        writeMax = size; //set wrap value for write header to new buffer size
    }

    //----------------------------------------------------------------
    //when new size is smaller than new size
    if (size < currentSize)
    {
        if (distance > size)
        {
            setDistance(size, false); //decrease delay time when new bufferSize is smaller than the current delay time
        }

        if ((writeHead > size && readHead < size) || (writeHead > size && readHead > size))
        {
            std::copy(buffer, buffer+size, newBuffer);
            readMax = writeHead;
            writeHead = 0; //set writeHead to begin of buffer 
            writeMax = size;
            waitingForResize = true; //if true, we wait with resizing until the writeHead is in front of the readHead
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

int CircBuffer::getSize() const
{
    return currentSize;
}



//Writes to the buffer
void CircBuffer::input (float value) 
{
    buffer[writeHead] = value;
    
}

//Reads from the buffer and interpolates decimal values
float CircBuffer::output() 
{
    if (!delayStarted)
        return 0.0f;
    else {
        if (ceil(readHead) == readHead || floor(readHead) == readHead)
        {
            return buffer[(int)readHead];
        } 
        else 
        {
            double low = buffer[(int)readHead];
            double high = buffer[readBuffer((int)readHead + 1)];
            double fraction = readHead - (int)readHead;
            double sample = Util::linearMap(fraction, low, high);
            return sample;
        }
    }
    
}



//Sets the delay instantly
void CircBuffer::setDistance (double distance, bool move) 
{   
    if (move)
    {
        if (distance < currentSize)
            newDistance = distance;
        else
            newDistance = currentSize-1;

        changeDistance = true;
    }
    else 
    {
        if (distance < currentSize) //if the new distance is greater than the buffer size
            this->distance = distance;            
        else
            this->distance = currentSize;


        if (!delayStarted)
            readHead = 0.0; //wait with incrementing the readhead until delay time is reached (when we first start the delay)
        else 
        {
            if (writeHead > distance) //if true then the writehead is in front of the readhead in the buffer
                readHead = writeHead - this->distance;
            else
                readHead = currentSize - this->distance + writeHead; //wrap readHead to end if it's in front of writeHead
        }
    }

}

//Returns the current delay time in samples
double CircBuffer::getDistance()
{
    if (writeHead < readHead)
        return currentSize - readHead + writeHead;
    else
        return ((double)writeHead - readHead);
}


//Increments the heads 1 position further
void CircBuffer::incrementHeads() 
{
    incrementWrite();
    incrementRead();

    if (changeDistance) //if we are gradually moving to a new delay time
    {
        distance = getDistance();
        if (distance < newDistance) //if new distance is larger than old distance
            readIncrement = 0.5;
        else if (distance > newDistance)
            readIncrement = 2.0;
        else if (distance == newDistance)
        {
            readIncrement = 1.0;
            // std::cout << "New delay time reached" << std::endl;
            changeDistance = false;
        }
    }
}

double CircBuffer::getReadPosition() const
{
    return readHead;
}

double CircBuffer::getWritePosition() const
{
    return writeHead;
}


inline void CircBuffer::wrapReadHeader (double& head) 
{
    if (head <= writeHead) 
        readMax = currentSize; //if buffer is resized (larger than old buf) when readHead is > writeHead then it wraps the readHead based on the old buffer size

    if (head >= readMax)
        head -= readMax;
}

inline int CircBuffer::readBuffer(double head)
{
    if (head >= readMax)
    head -= readMax;
    return head;
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
        readHead += readIncrement;
        wrapReadHeader(readHead);
    }

    if (waitingForResize) //wait for resizing until writeHead is in front of the readhead
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

void CircBuffer::deleteBuffer() 
{
        delete[] buffer;
}




