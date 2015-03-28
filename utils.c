#include "utils.h"

void printMatrix(probMatrix *matrix){
	printf("Number of genes: %d\n", matrix->genes);
	
	for(int i = 0; i < matrix->genes; i++){
		printf("\t%s\t", matrix->names[i]);
	}
	
	printf("\n");
	for(int i = 0; i < matrix->genes; i++){
		printf("%s\t", matrix->names[i]);
		for(int j = 0; j < matrix->genes; j++){
			printf("%lf\t", matrix->probabilityTable[i][j]);
		}
		printf("\n");
	}
}

int validation(probMatrix *matrix){
	for(int i = 0; i < matrix->genes; i++){
		for(int j = 0; j < matrix->genes; j++){
			// insert weird code here
		}
	}
	
	return 1; //valid
}
