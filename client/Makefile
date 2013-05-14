CC = gcc

all: clean client

again: clean client

client: client.o header.o
	$(CC) -o client client.o header.o

client.o:
	$(CC) -c client.c

header.o:
	$(CC) -c header.c

clean:
	rm -f *.o client
