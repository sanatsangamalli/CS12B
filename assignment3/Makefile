CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99 -g
OBJECTS = banhammer.o aes.o bv.o ll.o hash.o lex.yy.o 
.PHONY : all
all : banhammer.o aes.o bv.o ll.o hash.o lex.yy.o 
	: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o banhammer -lfl
banhammer : banhammer.o
	$(CC) $(OBJECTS) $(CFLAGS) -o banhammer -lfl
banhammer.o : banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c
aes.o : aes.c
	$(CC) $(CFLAGS) -c aes.c
bv.o : bv.c
	$(CC) $(CFLAGS) -c bv.c
ll.o : ll.c
	$(CC) $(CFLAGS) -c ll.c 
hash.o : hash.c
	$(CC) $(CFLAGS) -c hash.c
lex.yy.o : lex.yy.c
	$(CC) -c lex.yy.c
lex.yy.c: words.l
	flex words.l	
.PHONY : clean
clean :
	rm -f $(OBJECTS) banhammer aes bv hash lex.yy.o lex.yy.c