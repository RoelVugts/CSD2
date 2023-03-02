CXX= g++
CXXFLAGS = -I/usr/local/include -Wall -g -std=c++17
LDFLAGS= -ljack -ljsoncpp -lsndfile
SOURCE=main.o CircularBuffer.o oscillator.o sine.o sawtooth.o
TARGET=Effects

$(TARGET) : $(SOURCE)
	$(CXX) -o $@ $(SOURCE) $(LDFLAGS)

.cpp.o:
	$(CXX) -c $< $(CXXFLAGS)

clean:
	rm -f $(TARGET) *.o