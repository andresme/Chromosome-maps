CC=gcc
CFLAGS=-std=gnu99 -g
CHECK=-Wall -Wextra

mapper: utils.o file.o main.o list.o gnuplot_i.o
	$(CC) $(CHECK) $(CFLAGS) -o mapper utils.o file.o main.o list.o gnuplot_i.o 

clean: 
	rm -f *.o mapper
