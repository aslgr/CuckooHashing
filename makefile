CFLAGS = -Wall -g
LDFLAGS = -lm

CC = gcc

objects = myht.o hash.o
     
all: myht

myht: $(objects)
	$(CC) $^ -o $@ $(LDFLAGS)

myht.o: myht.c hash.h
	$(CC) -c $< $(CFLAGS)

hash.o: hash.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f $(objects)

purge:
	rm -f $(objects) myht