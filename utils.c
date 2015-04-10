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

int isValid(probMatrix *matrix){
	int isValid = 1;
	for(int i = 0; i < matrix->genes; i++){
		for(int j = i+1; j < matrix->genes - 1; j++){
			double sum1 = matrix->probabilityTable[i][j];
			for(int m = 1; j+m < matrix->genes; m++){
				double sum2 = matrix->probabilityTable[j][j+m];
				double checkSum = matrix->probabilityTable[i][j+m];
				if(cmpDouble(fabs(sum1-sum2), checkSum) != 1 &&
					cmpDouble(sum1 + sum2, checkSum) != 1){
						// printf("invalid: %d, %d +- %d, %d = %d, %d\n", i,j,j,j+m,i,j+m);
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

int isComplete(probMatrix *matrix){
	for(int i = 0; i < matrix->genes; i++){
		for(int j = i+1; j < matrix->genes; j++){
			if(cmpDouble(matrix->probabilityTable[i][j], -1) == 1){
				return 0;
			}
		}
	}
	return 1;
}

int isAlreadyCalculated(int i, int j, double value, ValueList *list){
	ValueNode *current = list->head;
	while(current != NULL){
		if(current->i == i && current->j == j && cmpDouble(current->value, value) == 1){
			return 1;
		}
		current = current->next;
	}
	return 0;
}

MatrixList* possibleNumber(probMatrix *matrix){
	MatrixList *list = emptyMatrixList();
	ValueList *values = emptyValueList();
	add(matrix, list);
	MatrixList *completeList = emptyMatrixList();

	MatrixNode * current = list->head;
	while(current != NULL){
		for(int i = 0; i < current->matrix->genes; i++){
			for(int j = i+1; j < current->matrix->genes - 1; j++){
				double sum1 = current->matrix->probabilityTable[i][j];
				for(int m = 1; i+m < current->matrix->genes; m++){
					double sum2 = current->matrix->probabilityTable[j][j+m];
					double checkSum = current->matrix->probabilityTable[i][j+m];
					double first = 0;
					double second = 0;
					int indexI = -1;
					int indexJ = -1;
					//printf("i:%d,j:%d,m:%d\n",i,j,m);
					if(cmpDouble(sum1, -1) == 1 && cmpDouble(sum2, -1) == 0 && cmpDouble(checkSum, -1) == 0){
						first = fabs(checkSum-sum2);
						second = checkSum+sum2;
						indexI = i;
						indexJ = j;
					} else if(cmpDouble(sum2, -1) == 1 && cmpDouble(sum1, -1) == 0 && cmpDouble(checkSum, -1) == 0){
						first = fabs(checkSum-sum1);
						second = checkSum+sum1;
						// printf("first: %f, second: %f\n", first, second);
						indexI = j;
						indexJ = j+m;
					} else if(cmpDouble(checkSum, -1) == 1 && cmpDouble(sum1, -1) == 0 && cmpDouble(sum2, -1) == 0){
						first = fabs(sum1-sum2);
						second = sum1+sum2;
						indexI = i;
						indexJ = j+m;
					}
					if(indexI != -1 && indexJ != -1){
						probMatrix* firstMatrix = copyMatrix(current->matrix);
						firstMatrix->probabilityTable[indexI][indexJ] = first;
						if(isComplete(firstMatrix) == 1 /*&& isAlreadyCalculated(indexI, indexJ, first, values) == 0*/){
							//printMatrix(firstMatrix);
							add(firstMatrix, completeList);
							addValue(indexI, indexJ, first, values);
						} else if(isAlreadyCalculated(indexI, indexJ, first, values) == 0){
							//printMatrix(firstMatrix);
							addValue(indexI, indexJ, first, values);
							add(firstMatrix, list);
						} else {
							free(firstMatrix);
						}
						if(cmpDouble(first, second) == 0){
							probMatrix* secondMatrix = copyMatrix(current->matrix);
							secondMatrix->probabilityTable[indexI][indexJ] = second;
							if(isComplete(secondMatrix) == 1 /*&& isAlreadyCalculated(indexI, indexJ, second, values) == 0*/){
							//	printMatrix(secondMatrix);
								add(secondMatrix, completeList);
								addValue(indexI, indexJ, second, values);
							} else if(isAlreadyCalculated(indexI, indexJ, second, values) == 0){
								//printMatrix(secondMatrix);
								addValue(indexI, indexJ, second, values);
								add(secondMatrix, list);
							} else {
								free(secondMatrix);
							}
						}
					}
				}
			}
		}
		current = current->next;
	}
	destroyValueList(values);
	return completeList;
}

GeneList * calculateGeneRoute(probMatrix *matrix){
	GeneList *map = emptyNodeList();
	int highestI = 0;
	int highestJ = 0;
	float largestDistance = 0;

	for(int i = 0; i < matrix->genes; i++){
		for(int j = i+1; j < matrix->genes - 1; j++){

		}
	}

	return map;
}

MapList * calculatePossibleMaps(MatrixList *matrices){
	MapList *result = emptyMapList();

	MatrixNode *current = matrices->head;
	while (current != NULL){
		addMap(calculateGeneRoute(current->matrix), result);
		current = current->next;
	}
	return result;
}
