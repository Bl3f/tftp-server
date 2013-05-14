CC = gcc

all: clean server

again: clean server

server: server.o header.o
	$(CC) -o server server.o header.o

server.o:
	$(CC) -c server.c

header.o:
	$(CC) -c header.c

clean:
	rm -f *.o server
