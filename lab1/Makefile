# This is a comment
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = hello.o cat.o
.PHONY : all
all : hello cat
 : $ (OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o concat
hello.o : hello.c
	$(CC) $(CFLAGS) -c hello.c
cat.o : cat.c
	$(CC) $(CFLAGS) -c cat.c
.PHONY : clean
clean :
	rm $(OBJECTS) hello cat
