#include "main.h"

int main(int argc, char *argv[]) {
	probMatrix* matrix = readFile(argv[1]);
	// MatrixList *list = emptyMatrixList();
	// add(matrix, list);
	// add(matrix, list);
	// display(list);
	MatrixList *possibles = possibleNumber(matrix);
	display(possibles);
	//printf("valid: %d\n	", isValid(matrix));
	return(0);
}
