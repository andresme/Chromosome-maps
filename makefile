CC=gcc
CFLAGS=-std=gnu99 -g `pkg-config --cflags gtk+-3.0` -Wl,--export-dynamic
LIBS   = `pkg-config --libs gtk+-3.0 gmodule-export-2.0`
CHECK=-Wall -Wextra



mapper: utils.o file.o main.o list.o gnuplot_i.o
	$(CC) $(CHECK) $(CFLAGS)  -o mapper utils.o file.o main.o list.o gnuplot_i.o $(LIBS)

clean: 
	rm -f *.o mapper
