CC = gcc
CFLAGS = -Wall

.PHONY: all clean

all: server client1 client2

server: server.c
	$(CC) $(CFLAGS) -o server.o server.c DieWithError.c

client1: client1.c
	$(CC) $(CFLAGS) -o client1.o client1.c DieWithError.c

client2: client2.c
	$(CC) $(CFLAGS) -o client2.o client2.c DieWithError.c

clean:
	rm -f server.o client1.o client2.o
