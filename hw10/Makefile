CC = gcc
CFLAGS = -Wall

.PHONY: all clean

all: sender receiver

sender: sender.c
	$(CC) $(CFLAGS) -o sender.o sender.c

receiver: receiver.c
	$(CC) $(CFLAGS) -o receiver.o receiver.c

clean:
	rm -f sender.o receiver.o
