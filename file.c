#include "file.h"

int main(int argc, char *argv[]) {
	probMatrix* matrix = readFile(argv[1]);
	printMatrix(matrix);
	return(0);
}


void printMatrix(probMatrix * matrix){
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



probMatrix* readFile(char* fileName) {
	char * fname;
	FILE *file;
	char content[1024], *token, *name, *number;
	double **matrix;
	file = fopen(fileName, "r");
	probMatrix *pMatrix;
	int genes = 0;
	int line = 0;
	int i = 0, j = 0;
	
	while (fgets(content, 1024, file)){
		token = strtok(content,"\n");
		while(token != NULL){
			if(line == 0){
				char* tokenTemp = (char *)malloc(strlen(token) * sizeof(char));
				strcpy(tokenTemp, token);
				name = strtok(token, ",");
				while(name != NULL){
					genes++;
					name = strtok(NULL, ",");
				}
				pMatrix = (probMatrix *) malloc(sizeof(probMatrix) + genes * sizeof(char *));
				pMatrix->genes = genes;
				name = strtok(tokenTemp, ",");
				int nameIndex = 0;
				while(name != NULL) {
					pMatrix->names[nameIndex] = (char *) malloc((strlen(name) + 1) * sizeof(char));
					strcpy(pMatrix->names[nameIndex], name);
					name = strtok(NULL, ",");
					nameIndex++;
				}
				pMatrix->probabilityTable = (double **) malloc(pMatrix->genes * sizeof(double *));
				for(int i = 0; i < pMatrix->genes; i++){
					pMatrix->probabilityTable[i] = (double *) malloc(pMatrix->genes * sizeof(double));
				}
				line++;
			} else {
				number = strtok(token,",");
				pMatrix->probabilityTable[i][j] = atof(number);
				j++;
				if(j >= pMatrix->genes){
					i++;
					j = 0;
				}
			}
			token = strtok(NULL, "\n");
		}
	}
	return pMatrix;
}
