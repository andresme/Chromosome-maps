#ifndef LIST_HEADER
#define LIST_HEADER

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "utils.h"

MatrixList * emptyMatrixList();
void add(probMatrix *matrix, MatrixList *list);
void display(MatrixList *list);
void destroy(MatrixList *list);
void delete(MatrixNode *node, MatrixList *list);
//void reverse(List * list);

GeneList * emptyNodeList();
void addGene(char *gene, double distance, GeneList *list);
void displayGeneList(GeneList *list);
void destroyGeneList(GeneList *list);
//void reverse(List * list);

#endif
