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

int gtDouble(double a, double b){
	return a > fabs(b - 0.0001);
}

int ltDouble(double a, double b){
	return a < fabs(b - 0.0001);
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

int compareMatrix(double **a, double **b, int size){
	for(int i = 0; i < size; i++){
		for(int j = i+1; j < size; j++){
			if(cmpDouble(a[i][j], b[i][j]) == 0){
				return 0;
			}
		}
	}
	return 1;
}

int isAlreadyCalculated(probMatrix *matrix, MatrixList *list){
	MatrixNode *current = list->head;
	if(current == NULL){
		return 0;
	}
	int isEqualToSomeMatrix = 0;
	
	while(current != NULL && isEqualToSomeMatrix == 0){
		isEqualToSomeMatrix = isEqualToSomeMatrix | compareMatrix(matrix->probabilityTable, current->matrix->probabilityTable, matrix->genes);
		current = current->next;
	}
	return isEqualToSomeMatrix;
}

MatrixList* possibleNumber(probMatrix *matrix){
	MatrixList *list = emptyMatrixList();
	add(copyMatrix(matrix), list);
	MatrixList *completeList = emptyMatrixList();
	MatrixNode *current = list->head;
	while(current != NULL){
		for(int i = 0; i < current->matrix->genes; i++){
			for(int j = i+1; j < current->matrix->genes - 1; j++){
				double sum1 = current->matrix->probabilityTable[i][j];
				for(int m = 1; i+m < current->matrix->genes-m; m++){
					double sum2 = current->matrix->probabilityTable[j][j+m];
					double checkSum = current->matrix->probabilityTable[i][j+m];
					double first = 0;
					double second = 0;
					int indexI = -1;
					int indexJ = -1;
					if(cmpDouble(sum1, -1) == 1 && cmpDouble(sum2, -1) == 0 && cmpDouble(checkSum, -1) == 0){
						first = fabs(checkSum-sum2);
						second = checkSum+sum2;
						indexI = i;
						indexJ = j;
					} else if(cmpDouble(sum2, -1) == 1 && cmpDouble(sum1, -1) == 0 && cmpDouble(checkSum, -1) == 0){
						first = fabs(checkSum-sum1);
						second = checkSum+sum1;
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
						if(isComplete(firstMatrix) == 1 && isAlreadyCalculated(firstMatrix, completeList) == 0){
							//printMatrix(firstMatrix);
							add(firstMatrix, completeList);
						} else if(isAlreadyCalculated(firstMatrix, list) == 0){
							//printMatrix(firstMatrix);
							add(firstMatrix, list);
						} else {
							destroyMatrix(firstMatrix);
						}
						if(cmpDouble(first, second) == 0){
							probMatrix* secondMatrix = copyMatrix(current->matrix);
							secondMatrix->probabilityTable[indexI][indexJ] = second;
							if(isComplete(secondMatrix) == 1 && isAlreadyCalculated(secondMatrix, completeList) == 0){
								//printMatrix(secondMatrix);
								add(secondMatrix, completeList);
							} else if(isAlreadyCalculated(secondMatrix, list) == 0){
								//printMatrix(secondMatrix);
								add(secondMatrix, list);
							} else {
								destroyMatrix(secondMatrix);
							}
						}
					}
				}
			}
		}
		current = current->next;
	}
	destroy(list);
	return completeList;
}

void destroyMatrix(probMatrix *matrix){
	for(int i = 0; i < matrix->genes; i++){
		free(matrix->names[i]);
	}
	for(int i = 0; i < matrix->genes; i++){
		free(matrix->probabilityTable[i]);
	}
	free(matrix->probabilityTable);
	free(matrix);
}

GeneList * calculateGeneRoute(probMatrix *matrix){
	GeneList *map = emptyNodeList();
	int highestI = 0;
	int highestJ = 0;
	double largestDistance = 0;

	for(int i = 0; i < matrix->genes; i++){
		for(int j = i+1; j < matrix->genes; j++){
			if (gtDouble(matrix->probabilityTable[i][j],largestDistance)){
				largestDistance = matrix->probabilityTable[i][j];
				highestI = i;
				highestJ = j;
			}
		}
	}

	int visited[matrix->genes];
	for(int i = 0; i < matrix->genes; i++){
		visited[i] = 0;
	}

	addGene(matrix->names[highestI], 0, map);
	visited[highestI] = 1;
	int currentI = highestI;
	int currentJ = 0;

	int nearestJ = currentJ;
	double nearestDistance = largestDistance;
	double value = 0;


	while(nearestJ != highestJ){
		while(currentJ < matrix->genes){
			value = matrix->probabilityTable[currentI][currentJ];
			if (cmpDouble(value, 0.0) == 1 && currentI != currentJ){
				value = matrix->probabilityTable[currentJ][currentI];
			}
			if (ltDouble(value, nearestDistance) == 1 && cmpDouble(value, 0.0) == 0 && visited[currentJ] == 0){
				nearestDistance = value;
				nearestJ = currentJ;
			}
			currentJ++;
		}

		addGene(matrix->names[nearestJ], value, map);
		visited[nearestJ] = 1;

		currentI = nearestJ;
		currentJ = 0;
		nearestDistance = largestDistance;
	}

	return map;
}

MapList * calculatePossibleMaps(MatrixList *matrices){
	MapList *result = emptyMapList();

	MatrixNode *current = matrices->head;
	while (current != NULL){
		if(isValid(current->matrix) == 1){
			printMatrix(current->matrix);
			addMap(calculateGeneRoute(current->matrix), result);
		}
		current = current->next;
	}
	return result;
}
