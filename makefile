CC=gcc
CFLAGS=-std=c99

mapper: utils.o file.o main.o
	$(CC) -o mapper utils.o file.o main.o $(CFLAGS)

clean: 
	rm -f *.o mapper
