CC=gcc
CFLAGS=-std=c99

mapper: utils.o file.o main.o
	$(CC) -o mapper utils.o file.o main.o -std=c99

clean: 
	rm -f *.o mapper
