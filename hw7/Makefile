CC = gcc
CFLAGS = -Wall

.PHONY: all clean

all: server client

server: server.c
	$(CC) $(CFLAGS) -o server.o server.c msg.h

client: client.c
	$(CC) $(CFLAGS) -o client.o client.c msg.h

clean:
	rm -f server.o client.o
