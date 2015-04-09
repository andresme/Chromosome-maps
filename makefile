CC=gcc
CFLAGS=-std=gnu99

mapper: utils.o file.o main.o list.o gnuplot_i.o
	$(CC) -o mapper utils.o file.o main.o list.o gnuplot_i.o $(CFLAGS)

clean: 
	rm -f *.o mapper
