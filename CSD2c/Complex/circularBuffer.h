#include <iostream>
#include <type_traits>
#include <cmath>

#include "util.h"

#pragma once

template<class dataType, class headType> 
class CircBuffer {
    using uint = unsigned int;
    
public:
    CircBuffer (uint size) : buffer (new dataType[size]), currentSize (size), newBuffer(nullptr)
    { 
        //initialize writeHeader to buffer size
        readMax = size;

        isPowerOfTwo(size);

        //initialize all samples to 0
        for (uint i = 0; i < size; i++)
            buffer[i] = 0.0;
    }

    ~CircBuffer()
    {
        deleteBuffer();
    }

    //changes the size of the buffer in samples
    void setSize(uint size)
    {
        newBuffer = new dataType[size];

        if (size == currentSize)
            return; //exit function if size is not changed
        else
        {
            if (size < currentSize)
                std::copy(buffer, buffer+size, newBuffer); //copy contents of old buf to new buf
            else
                std::copy(buffer, buffer+currentSize, newBuffer);

            delete[] buffer; //delete old buf
            buffer = newBuffer; //set new buffer to the buffer we will be using
            currentSize = size;
        }
        isPowerOfTwo(currentSize);
    }

    //return the size of the buffer in samples
    uint getSize() const
    {
        return currentSize;
    }

    //writes to the buffer at the current writeHead position
    void writeSample(dataType value)
    {
        buffer[writeHead] = value;
    }

    /*reads from the buffer at writeHead - delay (in samples)
    Note that you should always read before you write to access the oldest sample in the delay.
    Also note that if for some reason you want a delay of 0 samples you should always write before you read.
    */
    dataType readSample(headType delay)
    {
        //limit delay to bufferSize
        if (delay > currentSize)
            delay = currentSize;
        else if (delay <= 0)
            delay = 0;
        
        /*set delayStarted to true when the writePos has written the samples at
        delay -1. -1 because delay is entered in sample amount and buffer starts at index [0].
        */
        if ((int)writeHead >= (int)delay - 1)
            delayStarted = true;

        //return 0 if the buffer at index writeHead - delay is not filled yet
        if (!delayStarted)
            return 0.0f;
        else 
        {
            if (delay > writeHead)
                delay = readMax - delay + writeHead; //wrap readPos
            else 
                delay = writeHead - delay;
            
            //check if the readIndex is an int or uint
            if (std::is_same<headType, int>::value || std::is_same<headType, uint>::value)
            {
                return buffer[(int)delay];
            }
            else 
            {
                dataType low = buffer[(int)delay];
                dataType high = buffer[wrapRead((int)delay + 1)];
                headType fraction = delay - (int)delay;
                dataType sample = Util::linearMap(fraction, low, high);
                return sample;
            }
        } 
    }

    //increments the writeHead with 1
    void incrementWrite()
    {
        writeHead++;
        wrapWriteHeader(writeHead);

        /*if statement that protects the user from reading positions that have not been written yet
        when the buffer has been resized (to a larger buffer). This wraps the readPos based on the 
        old buffer size until the write head has passed the old size*/
        if (writeHead > readMax)
            readMax = currentSize;
    }

    //returns the writeHead position
    uint getWritePosition() const
    {
        return writeHead;
    }  


private:
    inline int wrapRead(headType head)
    {
        if (head >= readMax)
        head -= readMax;
        return head;
    }

    inline void wrapWriteHeader (uint& head)
    {
        if (bufferIsPowerOfTwo)
            head &= mask;
        else {
            if (head >= currentSize)
                head -= currentSize;
        }
    }
    
    inline void deleteBuffer()
    {
        delete[] buffer;
    }

    //checks if the buffer is a power of 2 (for faster calculations)
    inline void isPowerOfTwo(int number)
    {
        if (number <= 0)
            bufferIsPowerOfTwo = false;
        else if ((number & (number-1)) == 0 )
        {
            bufferIsPowerOfTwo = true;
            mask = number - 1;
        } else
            bufferIsPowerOfTwo = false;
    }


    bool delayStarted { false };
    bool waitingForResize { false };
    bool bufferIsPowerOfTwo {false };
    int mask { 0 };

    dataType* buffer;
    uint currentSize { 0 };
    dataType* newBuffer;
    uint writeHead { 0 };
    headType readMax { 0 };

};