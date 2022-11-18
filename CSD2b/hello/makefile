# Makefile voor HelloGoodbye
#
# Marc_G 2012

CC = g++
CFLAGS = -Wall
PROG = hello
SRC = hello.cpp hello_main.cpp
OBJS = hello.o hello_main.o

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS)
	rm $(OBJS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	/bin/rm -f $(PROG) $(OBJS)
	

depend:
	makedepend $(SRC)

