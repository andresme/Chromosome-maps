#ifndef _UTILS_H_

#define _UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <tgmath.h>
#include "structs.h"
#include "list.h"

void printMatrix(probMatrix * matrix);
void destroyMatrix(probMatrix *matrix);
int cmpDouble(double a, double b);
int isValid(probMatrix *matrix);
int isAlreadyCalculated(probMatrix *matrix, MatrixList *list);
ValueList* predictCrossOver(probMatrix *matrix, char* i, char* j);
MatrixList* possibleNumber(probMatrix *matrix);
MapList * calculatePossibleMaps(MatrixList *matrices);

#endif
