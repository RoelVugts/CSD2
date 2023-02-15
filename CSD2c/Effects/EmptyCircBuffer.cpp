#include "EmptyCircBuffer.h"
#include "Util.h"

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
    if (ceil(readHead) == readHead || floor(readHead) == readHead)
    {
        if (changeDistance)
        {
            std::cout << "readPos: " << readHead << std::endl;
            std::cout << "writePos: " << writeHead << std::endl;
            std::cout << "distance: " << distance << std::endl;
            std::cout << "calculated: " << getDistance() << std::endl;
            std::cout << "Sample: " << buffer[(int)readHead] << std::endl;
            std::cout << "\n" << std::endl;
        }
        return buffer[(int)readHead];
    } 
    else 
    {
        double low = buffer[(int)readHead];
        double high = buffer[readBuffer((int)readHead + 1)];
        double fraction = readHead - (int)readHead;
        double sample = Util::linearMap(fraction, low, high);
        std::cout << "readPos: " << readHead << std::endl;
        std::cout << "writePos: " << writeHead << std::endl;
        std::cout << "distance: " << distance << std::endl;
        std::cout << "calculated: " << getDistance() << std::endl;
        std::cout << "newDistance: " << newDistance << std::endl;
        std::cout << "Sample: " << sample << std::endl;
        std::cout << "\n" << std::endl;
        return sample;
    }
    
}

inline int CircBuffer::readBuffer(double head)
{
    if (head >= readMax)
    head -= readMax;
    return head;
}

//Setters
//----------------------------------------------------------------------





//Returns the current delay time in samples
double CircBuffer::getDistance()
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

double CircBuffer::getReadPosition() const
{
    return readHead;
}

double CircBuffer::getWritePosition() const
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
            setDistance(size); //decrease delay time when new bufferSize is smaller than the current delay time
        }

        if ((writeHead > size && readHead < size) || (writeHead > size && readHead > size))
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

void CircBuffer::deleteBuffer() 
{
        delete[] buffer;
}

//---------------------------------------------------------------------------------

//Increments the heads 1 position further
void CircBuffer::incrementHeads() 
{
    incrementWrite();
    incrementRead();

    if (changeDistance)
    {
        distance = getDistance();
        if (distance < newDistance) //if new distance is larger than old distance
            readIncrement = 0.5;
        else if (distance > newDistance)
            readIncrement = 2.0;
        else if (distance == newDistance)
        {
            readIncrement = 1.0;
            changeDistance = false;
        }
    }
}

//Private functions
//--------------------------------------------------------------------------------
inline void CircBuffer::wrapReadHeader (double& head) 
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
        readHead += readIncrement;
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

//Sets the delay instantly
void CircBuffer::setDistance (double distance) 
{   
    if (distance < currentSize) //if the new distance is greater than the buffer size
    {
        this->distance = distance;
    }
        
    else
        this->distance = currentSize;


    if (!delayStarted)
        readHead = 0.0;
    else 
    {
        if (writeHead > distance) //if true then the writehead is in front of the readhead in the buffer
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
void CircBuffer::setDistance(double distance, int time)
{
    newDistance = distance;
    changeDistance = true;

}


