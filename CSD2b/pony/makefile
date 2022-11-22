# Makefile voor HelloGoodbye
#
# Marc_G 2012 (Aangepast door Roel Vugts)

NAME = pony #enter name here

CC = g++
CFLAGS = -Wall
PROG = $(NAME)
SRC = $(NAME).cpp $(NAME)_main.cpp
OBJS = pony.o pony_main.o

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS)
	@rm $(OBJS)
	@echo "\n" 
	@./$(NAME) 

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	/bin/rm -f $(PROG) $(OBJS)
	
depend:
	makedepend $(SRC)
