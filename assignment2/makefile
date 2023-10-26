CC = gcc

CFlags = -Wall -g

LD = gcc

LDFLAGS = 

.SILENT:

all: fw

fw: hashtable.o readtext.o
	$(LD) $(LDFLAGS) -o fw hashtable.o readtext.o

hashtable.o: hashtable.c
	$(CC) -c -o $(CFLAGS) hashtable.o hashtable.c

readtext.o: readtext.c
	$(CC) -c -o $(CFLAGS) readtext.o readtext.c

test: fw
	valgrind --leak-check=yes ./fw emptyfile

testhashtable: hashtable
	valgrind --leak-check=yes ./hashtable < TestInput1 > hashtable.out

clean:
	rm -f *.o fw
