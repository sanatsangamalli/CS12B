# This is a comment
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = parfait.o bv.o sieve.o 
.PHONY : all
all : bv.o sieve.o parfait.o
	: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(CFLAGS) -o parfait -lm
parfait : parfait.o
	$(CC) $(OBJECTS) $(CFLAGS) -o parfait -lm
parfait.o : parfait.c
	$(CC) $(CFLAGS) -c parfait.c
bv.o : bv.c
	$(CC) $(CFLAGS) -c bv.c
sieve.o : sieve.c
	$(CC) $(CFLAGS) -c sieve.c 
.PHONY : clean
clean :
	rm -f $(OBJECTS) parfait bv sieve
