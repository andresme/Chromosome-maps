#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
	int genes;
	double **probabilityTable;
	char *names[];
} probMatrix;

void printMatrix(probMatrix * matrix);
