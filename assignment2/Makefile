CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = sorting.o bv.o minsort.o bubblesort.o insertionsort.o quicksort.o mergesort.o
.PHONY : all
all : sorting.o bv.o minsort.o bubblesort.o insertionsort.o quicksort.o mergesort.o
	: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -g -o sorting 
sorting : sorting.o
	$(CC) $(OBJECTS) $(CFLAGS) -o sorting 
sorting.o : sorting.c
	$(CC) $(CFLAGS) -DMASK=0x00ffffff -c sorting.c
bv.o : bv.c
	$(CC) $(CFLAGS) -c bv.c
minsort.o : minsort.c
	$(CC) $(CFLAGS) -c minsort.c 
bubblesort.o : bubblesort.c
	$(CC) $(CFLAGS) -c bubblesort.c
insertionsort.o : insertionsort.c
	$(CC) $(CFLAGS) -c insertionsort.c
quicksort.o : quicksort.c
	$(CC) $(CFLAGS) -c quicksort.c
mergesort.o : mergesort.c
	$(CC) $(CFLAGS) -c mergesort.c
.PHONY : clean
clean :
	rm -f $(OBJECTS) sorting bv minsort bubblesort insertionsort quicksort mergesort