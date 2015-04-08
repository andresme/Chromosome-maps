#include "main.h"

int main(int argc, char *argv[]) {
	probMatrix* matrix = readFile(argv[1]);
	// MatrixList *list = emptyMatrixList();
	// add(matrix, list);
	// add(matrix, list);
	// display(list);
	possibleNumber(matrix);
	//printf("valid: %d\n	", checkValidity(matrix));
	return(0);
}
