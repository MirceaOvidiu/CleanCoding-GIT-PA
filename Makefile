#!/bash
CC=gcc
CFLAGS=-Wall
LDFLAGS=
#for libraries

all: ex1 ex2

#objects
ex1.o: example1.c
	$(CC) -c -o $@ $< $(CFLAGS)

ex2.o: example2.c 
	$(CC) -c -o $@ $< $(CFLAGS)


#executables
ex1: ex1.o 
	$(CC) -o $@ $^ $(LDFLAGS) 

ex2: ex2.o 
	$(CC) -o $@ $^ $(LDFLAGS) 

debug1: example1.c
	$(CC) -g -o debug1 $^ $(CFLAGS)

debug2: example2.c
	$(CC) -g -o debug2 $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o ex1 ex2 debug1 debug2
