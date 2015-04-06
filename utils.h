#ifndef _UTILS_H_

#define _UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <tgmath.h>

typedef struct {
	int genes;
	double **probabilityTable;
	char *names[];
} probMatrix;

void printMatrix(probMatrix * matrix);
int cmpDouble(double a, double b);
int checkValidity(probMatrix *matrix);

#endif
