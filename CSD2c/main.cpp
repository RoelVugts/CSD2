#include "EmptyCircBuffer.h"

#include <iostream>
#include <cmath>
#include <unistd.h>

int main()
{
    CircBuffer buffer(16);
    buffer.setDistance(4);

    float amplitude = 1.0f;
    float phaseDelta = sin(2*3.14*440);
    float phase = 0.0f;


    //fill buffer with sine wave
    for (int i = 0; i < buffer.getSize(); i++)
    {
        float sample = amplitude * sin(phase);
        buffer.input(sample);
        buffer.incrementHeads();
        phase += phaseDelta;
    }


    //output buffer
    for (int i = 0; i < buffer.getSize()*1; i++)
    {
        std::cout << "ReadHead: " << buffer.getReadPosition() << "   WriteHead: " << buffer.getWritePosition() << "    Value: " << buffer.output() << std::endl;
        buffer.incrementHeads();
        usleep(50000);
    }


    //change size of buffer
    std::cout << "Old size: " << buffer.getSize() << std::endl;
    buffer.setSize(24);
    std::cout << "----------------------" << std::endl;
    std::cout << "New size: " << buffer.getSize() << std::endl;

    //increment distance slowly to new distance
    buffer.setDistance(10, 500);

    //output buffer
    for (int i = 0; i < buffer.getSize()*5; i++)
    {
        std::cout << "writeHead: " << buffer.getWritePosition() << "   readHead: " << buffer.getReadPosition() << "    Value: " << buffer.output() << std::endl;
        buffer.incrementHeads();
        usleep(100000);

        if (i == 50)
        {
            std::cout << "set new size\n" << std::endl;
            buffer.setSize(15);
        }
    }

    buffer.t.join();

    return 0;
}