#ifndef _STRUCTS_H

#define _STRUCTS_H

typedef struct {
	int genes;
	double **probabilityTable;
	char *names[];
} probMatrix;

typedef struct valueNode{
	char *i;
	char *j;
	double value;
	struct valueNode *next;
} ValueNode;

typedef struct valueList {
	ValueNode *head;
} ValueList;

typedef struct matrixNode {
  probMatrix *matrix;
  struct matrixNode *next;
} MatrixNode;

typedef struct matrixList {
  MatrixNode * head;
} MatrixList;


typedef struct geneNode {
  char *gene;
  double distance;
  struct geneNode *next;
} GeneNode;

typedef struct geneList {
  GeneNode * head;
} GeneList;

typedef struct mapNode {
  GeneList *map;
  struct mapNode *next;/* data */
} MapNode;

typedef struct mapList {
  MapNode * head;
} MapList;

#endif
