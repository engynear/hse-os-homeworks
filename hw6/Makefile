CC = gcc
CFLAGS = -Wall

.PHONY: all clean

all: server client

server: server.c
	$(CC) $(CFLAGS) -o server.o server.c shared_memory.c

client: client.c
	$(CC) $(CFLAGS) -o client.o client.c shared_memory.c

clean:
	rm -f server.o client.o
