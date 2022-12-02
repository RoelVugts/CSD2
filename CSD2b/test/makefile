# Makefile voor HelloGoodbye
#
# Marc_G 2012

NAME = main #enter name here


CXX := g++
CXXFLAGS := -Wall -g -std=c++14
TARGET := Test

# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<
clean:
	rm -f $(TARGET) *.o