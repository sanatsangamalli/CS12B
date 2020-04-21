CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99 -g -lpthread
CC = gcc

.PHONY: all
all: increment

increment: increment.o  
	$(CC) $(CFLAGS) -o increment increment.o  
increment.o: increment.c
	$(CC) $(CFLAGS) -c increment.c
	
.PHONY: clean
clean:
	rm -f increment increment.o 
