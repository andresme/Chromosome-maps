#ifndef LIST_HEADER
#define LIST_HEADER

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct matrixNode {
  probMatrix *matrix;
  struct matrixNode *next;
} MatrixNode;

typedef struct matrixList {
  MatrixNode * head; 
} MatrixList;

MatrixList * emptyMatrixList();
void add(probMatrix *matrix, MatrixList *list);
void display(MatrixList *list);
void destroy(MatrixList *list);
void delete(MatrixNode *node, MatrixList *list);
//void reverse(List * list);

#endif
