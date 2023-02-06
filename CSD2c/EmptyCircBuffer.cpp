#include "EmptyCircBuffer.h"

void CircBuffer::input (float value) {
    buffer[writeHead] = value;
}
float CircBuffer::output() {
    return buffer[readHead];
}

void CircBuffer::setDistance (uint distance) {
    readHead = writeHead - distance;
}

void CircBuffer::incrementHeads() {
    incrementWrite();
    incrementRead();
}

inline void CircBuffer::wrapHeader (uint& head) {
    if (head > currentSize)
        head -= currentSize;
}
inline void CircBuffer::incrementWrite() {
    wrapHeader(writeHead++);
}
inline void CircBuffer::incrementRead() {
    wrapHeader(readHead++);
}

void CircBuffer::deleteBuffer() {
    
    // for (buf : buffer)
    //     buffer[buf] = 0.0f;

        delete buffer;
}