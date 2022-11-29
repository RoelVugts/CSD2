CXX= g++
CXXFLAGS = -I/usr/local/include -Wall -std=c++17
LDFLAGS= -ljack
SOURCE=sine.o main.o oscillator.o square.o sawtooth.o
TARGET=Synth

$(TARGET) : $(SOURCE)
	$(CXX) -o $@ $(SOURCE) $(LDFLAGS)

.cpp.o:
	$(CXX) -c $< $(CXXFLAGS)

clean:
	rm -f $(TARGET) *.o
