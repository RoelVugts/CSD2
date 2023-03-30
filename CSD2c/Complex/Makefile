CXX= g++
CXXFLAGS = -I/usr/local/include -Wall -std=c++17
SOURCE=main.o UI.o util.o
TARGET=Complex

$(TARGET) : $(SOURCE)
	$(CXX) -o $@ $(SOURCE) $(LDFLAGS)

.cpp.o:
	$(CXX) -c $< $(CXXFLAGS)

clean:
	rm -f $(TARGET) *.o