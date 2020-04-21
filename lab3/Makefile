CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99 -g
OBJECTS = gdbLab.o 
.PHONY : all
all : gdbLab.o 
	: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o gdbLab -lm
gdbLab : gdbLab.o
	$(CC) $(OBJECTS) $(CFLAGS) -o gdbLab -lm
gdbLab.o : gdbLab.c
	$(CC) $(CFLAGS) -c gdbLab.c
.PHONY : clean
clean :
	rm -f $(OBJECTS) gdbLab