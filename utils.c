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
			double sum1 = matrix->probabilityTable[i][j];
			for(int m = 1; i+m < matrix->genes; m++){
				double sum2 = matrix->probabilityTable[j][j+m];
				double checkSum = matrix->probabilityTable[i][j+m];		
				if(cmpDouble(sum1, 0) != 1 && cmpDouble(sum2, 0) != 1 && cmpDouble(fabs(sum1-sum2), checkSum) != 1 &&
					cmpDouble(sum1 + sum2, checkSum) != 1){
						isValid = 0;
						break;
				}
			}
			if(isValid == 0) break;
		}
		if(isValid == 0) break;
	}
	
	return isValid;
}

probMatrix* copyMatrix(probMatrix *matrix){
	probMatrix* pMatrix = (probMatrix *) malloc(sizeof(probMatrix) + matrix->genes * sizeof(char *));
	pMatrix->genes = matrix->genes;
	
	for(int i = 0; i < matrix->genes; i++){
		pMatrix->names[i] = (char *) malloc((strlen(matrix->names[i]) + 1) * sizeof(char));
		strcpy(pMatrix->names[i], matrix->names[i]);
		
	}
	
	pMatrix->probabilityTable = (double **) malloc(pMatrix->genes * sizeof(double *));
	for(int i = 0; i < pMatrix->genes; i++){
		pMatrix->probabilityTable[i] = (double *) malloc(pMatrix->genes * sizeof(double));
		for(int j = 0; j < pMatrix->genes; j++){
			pMatrix->probabilityTable[i][j] = matrix->probabilityTable[i][j];
		}
	}
	return pMatrix;
}

void possibleNumber(probMatrix *matrix){
	MatrixList *list = emptyMatrixList();
	for(int i = 0; i < matrix->genes; i++){
		for(int j = i+1; j < matrix->genes - 1; j++){
			double sum1 = matrix->probabilityTable[i][j];
			double sum2 = matrix->probabilityTable[j][j+1];
			double checkSum = matrix->probabilityTable[i][j+1];
			
			if(cmpDouble(sum1, -1) == 1){
				double first = fabs(checkSum-sum2);
				double second = checkSum+sum2;
				
				probMatrix* firstMatrix = copyMatrix(matrix);
				firstMatrix->probabilityTable[i][j] = first;
				add(firstMatrix, list);
				
				probMatrix* secondMatrix = copyMatrix(matrix);
				secondMatrix->probabilityTable[i][j] = second;
				add(secondMatrix, list);
			}
		}
	}
	MatrixNode * current = list->head;
	if(list->head == NULL) 
		return;
	while(current->next != NULL){
		printMatrix(current->matrix);
		current = current->next;
	}
	printMatrix(current->matrix);
}



