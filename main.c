#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#define SCALE 1000

int main(int argc, char *argv[]){
	probMatrix* matrix = readFile(argv[1]);
	//printMatrix(matrix);
	
	MatrixList *possibles = possibleNumber(matrix);
	MapList *maps = calculatePossibleMaps(possibles);
	//displayMapList(maps);
	plotMaps(maps);
	
	//displayMapList(maps);
	destroyMatrix(matrix);
	destroy(possibles);
	destroyMapList(maps);
	
    while(1){
	 	//tiene que seguir corriendo para poder hacer zoom/pan
	 	printf(" ");
	};
	return 0;
}


int GetNumberOfDigits (int i)
{
    int digits = 0; do { i /= 10; digits++; } while (i != 0);
    return digits;
}


void plotMaps(MapList *list){
	gnuplot_ctrl* h1;
	h1 = gnuplot_init();
	
	MapNode *current = list->head;
	char *cmd = "%1.4f title 'map %d', \\";
	char *pattern = "%1.4f title 'map %d'";
	char *label = "set label '%s' at %1.4f,%1.4f";
	int i = 0;
	
	if(current != NULL){
		gnuplot_cmd(h1, "set xrange[0:0.5]");
		gnuplot_cmd(h1, "set yrange[0:0.010]");
		gnuplot_cmd(h1, "plot \\");
	} else {
		printf("No maps found\n");
		return;
	}
	while(current->next != NULL){
		int digits = GetNumberOfDigits(i);
		char *currentCmd = malloc((digits + 23) * sizeof(char));
		sprintf(currentCmd, cmd, ((double)i)/SCALE, i);
		printf("%s\n", currentCmd);
		gnuplot_cmd(h1, currentCmd);
		i++;
		current = current->next;
		free(currentCmd);
	}
	if(i == 0){
		gnuplot_cmd(h1, "0 title 'map 0'");
	} else {
		int digits = GetNumberOfDigits(i);
		char *lastCmd = malloc((digits + 19) * sizeof(char));
		sprintf(lastCmd, pattern, ((double)i)/SCALE, i);
		//printf("%s\n", lastCmd);
		gnuplot_cmd(h1, lastCmd);
		free(lastCmd);
	}
	
	current = list->head;
	i = 0;
	while(current != NULL){
		double value = 0.0;
		GeneNode *node = current->map->head;
		
		while(node != NULL){
			int digits = GetNumberOfDigits(i);
			char *labelCmd = malloc((24 + strlen(node->gene)) * sizeof(char));
			value = value + node->distance;
			sprintf(labelCmd, label, node->gene, value, ((double)i)/SCALE);
			//printf("%s\n", labelCmd);
			gnuplot_cmd(h1, labelCmd);
			node = node->next;
			free(labelCmd);
		}
		current = current->next;
		i++;
	}
}

