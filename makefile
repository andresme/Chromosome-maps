CC=gcc
CFLAGS=-std=c99

mapper: utils.o file.o main.o list.o 
	$(CC) -o mapper utils.o file.o main.o list.o $(CFLAGS)

clean: 
	rm -f *.o mapper
