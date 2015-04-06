#include "main.h"


int main(int argc, char *argv[]) {
	probMatrix* matrix = readFile(argv[1]);
	printf("valid: %d\n	", checkValidity(matrix));
	return(0);
}
