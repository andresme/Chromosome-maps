#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#define NUM_MAPS 5
#define NUM_COMMANDS 2

int main(int argc, char *argv[]){
	
	probMatrix* matrix = readFile(argv[1]);
	MatrixList *possibles = possibleNumber(matrix);
	display(possibles);
	
    gnuplot_ctrl* h1;
	MapList *possibleMaps = calculatePossibleMaps(possibles);

    printf("*** example of gnuplot control through C ***\n") ;
    h1 = gnuplot_init();
    gnuplot_resetplot(h1);
	gnuplot_cmd(h1, "set title 'Chromosomic maps'");	
	gnuplot_cmd(h1, "plot 0 title 'map 1', 15 title 'map 2', 30 title 'map 3'");
    gnuplot_cmd(h1, "set label \"A\" at 0,0");
    gnuplot_cmd(h1, "set label \"B\" at 0,15");
    gnuplot_cmd(h1, "set label \"C\" at 0,30");
    while(1){
		//tiene que seguir corriendo para poder hacer zoom/pan
		printf("ruuuuuuuuu");
		printf("uuuun");
	};
	return 0;
}
