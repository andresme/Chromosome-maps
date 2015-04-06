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

int cmpDouble(double a, double b){
	return fabs(a - b) < 0.0001;
}

int checkValidity(probMatrix *matrix){
	int isValid = 1;
	for(int i = 0; i < matrix->genes; i++){
		for(int j = i+1; j < matrix->genes - 1; j++){
			//printf("checking [%d][%d] +- [%d][%d] == [%d][%d]\n", i, j, j, j+1, i, j+1);
			
			double sum1 = matrix->probabilityTable[i][j];
			double sum2 = matrix->probabilityTable[j][j+1];
			double checkSum = matrix->probabilityTable[i][j+1];
			
			//printf("checking %f +- %f == %f | %f | %f \n", sum1, sum2, checkSum, fabs(sum1-sum2), sum1+sum2);
			
			//printf("check1: %d\n", cmpDouble(sum1, 0));
			//printf("check2: %d\n", cmpDouble(sum2, 0));
			//printf("check3: %d\n", cmpDouble(fabs(sum1-sum2), checkSum));
			//printf("check4: %d\n", cmpDouble(sum1 + sum2, checkSum));
			
			//printf("=========================\n");
			
			if(cmpDouble(sum1, 0) != 1 && cmpDouble(sum2, 0) != 1 && cmpDouble(fabs(sum1-sum2), checkSum) != 1 &&
				cmpDouble(sum1 + sum2, checkSum) != 1){
					isValid = 0;
					break;
			}
		}
		if(isValid == 0) break;
	}
	
	return isValid;
}
