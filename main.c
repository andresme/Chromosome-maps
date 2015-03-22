#include "main.h"

#define ROWS 10

double **probabilityTable;

int main(int argc, char *argv[]) {
	test();
	
	
	return(0);
}

void test() {
	probabilityTable = (double **) malloc(ROWS * sizeof(double *));
	
	for(int i = 0; i < ROWS; i++){
		probabilityTable[i] = (double *) malloc(ROWS * sizeof(double));
	}
	
	probabilityTable[0][0] = 0.0d;
	probabilityTable[0][1] = 0.05d;
	probabilityTable[0][2] = 0.07d;
	probabilityTable[0][3] = 0.15d;
	probabilityTable[1][1] = 0.0d;
	probabilityTable[1][2] = 0.02d;
	probabilityTable[1][3] = 0.10d;
	probabilityTable[2][2] = 0.0d;
	probabilityTable[2][3] = 0.08d;
	probabilityTable[3][3] = 0.0d;
	
	for(int i = 0; i < ROWS; i++) {
		for(int j = 0; j < ROWS; j++) {
			printf("%lf, ", probabilityTable[i][j]);
		}
		printf("\n");
	}
}
