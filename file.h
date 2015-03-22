#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
	int genes;
	double **probabilityTable;
	char *names[];
} probMatrix;


probMatrix* readFile(char* fileName);
void printMatrix(probMatrix * matrix);
