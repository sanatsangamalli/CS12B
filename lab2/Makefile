# This is a comment
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = arraylist.o 
.PHONY : all
all : arraylist.o
	: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o arraylist 
arraylist : arraylist.o
	$(CC) $(OBJECTS) $(CFLAGS) -o arraylist 
.PHONY : clean
clean :
	rm -f $(OBJECTS) arraylist
