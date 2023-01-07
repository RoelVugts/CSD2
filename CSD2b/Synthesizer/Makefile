CXX= g++
CXXFLAGS = -I/usr/local/include -Wall -g -std=c++17
LDFLAGS= -ljack -ljsoncpp
SOURCE=main.o sine.o oscillator.o square.o sawtooth.o melGen.o synth.o callback.o audioToFile.o timer.o superSynth.o FmSynth.o UI.o env.o filter.o
TARGET=Synth

$(TARGET) : $(SOURCE)
	$(CXX) -o $@ $(SOURCE) $(LDFLAGS)

.cpp.o:
	$(CXX) -c $< $(CXXFLAGS)

clean:
	rm -f $(TARGET) *.o
