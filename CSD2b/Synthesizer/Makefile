CXX= g++
CXXFLAGS = -I/usr/local/include -Wall -g -std=c++17
LDFLAGS= -ljack
SOURCE=main.o sine.o oscillator.o square.o sawtooth.o melGen.o synth.o callback.o audioToFile.o antiAliasedOsc.o antiAliasedSquare.o antiAliasedSaw.o timer.o superSynth.o FmSynth.o UI.o
TARGET=Synth

$(TARGET) : $(SOURCE)
	$(CXX) -o $@ $(SOURCE) $(LDFLAGS)

.cpp.o:
	$(CXX) -c $< $(CXXFLAGS)

clean:
	rm -f $(TARGET) *.o
