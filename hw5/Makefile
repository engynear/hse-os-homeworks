CC = gcc
CFLAGS = -Wall

.PHONY: all clean

all: writer reader

writer: writer.c
	$(CC) $(CFLAGS) -o writer.o writer.c

reader: reader.c
	$(CC) $(CFLAGS) -o reader.o reader.c

clean:
	rm -f writer.o reader.o
