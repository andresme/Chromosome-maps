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

GeneList * emptyNodeList();
void addGene(char *gene, double distance, GeneList *list);
void displayGeneList(GeneList *list);
void reverse(GeneList * list);
void destroyGeneList(GeneList *list);

ValueList *emptyValueList();
void addValue(int i, int j, double value, ValueList *list);
void displayValueList(ValueList *list);
void destroyValueList(ValueList *list);


MapList * emptyMapList();
void addMap(GeneList *map, MapList *list);
void displayMapList(MapList *list);
void destroyMapList(MapList *list);

#endif
