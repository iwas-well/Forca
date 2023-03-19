CC = gcc

CFLAGS = -g -Wall

all: forca

forca: forca.o
	$(CC) $(CFLAGS) forca.o -o forca

forca.o: forca.c
	$(CC) $(CFLAGS) -c forca.c -o forca.o

clean: 
	-rm -f *.o

purge:	clean
	-rm forca
