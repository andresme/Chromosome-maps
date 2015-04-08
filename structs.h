#ifndef _STRUCTS_H

#define _STRUCTS_H

typedef struct {
	int genes;
	double **probabilityTable;
	char *names[];
} probMatrix;


typedef struct matrixNode {
  probMatrix *matrix;
  struct matrixNode *next;
} MatrixNode;

typedef struct matrixList {
  MatrixNode * head; 
} MatrixList;

#endif
