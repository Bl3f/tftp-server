CC = gcc

all: clean server client

again: clean server client

server: server.o header.o
	$(CC) -o server server.o header.o

client: client.o header.o
	$(CC) -o client client.o header.o

client.o:
	$(CC) -c client.c

server.o:
	$(CC) -c server.c

header.o:
	$(CC) -c header.c

clean:
	rm -f *.o server client
