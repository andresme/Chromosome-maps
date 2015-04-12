#include "file.h"

probMatrix* readFile(char* fileName) {
	FILE *file;
	char content[1024], *token, *name, *number;
	probMatrix *pMatrix;
	int genes = 0;
	int line = 0;
	int i = 0, j = 0;
	
	file = fopen(fileName, "r");
	if(file == NULL){
		printf("Error reading file");
		exit(1);
	}
	
	while (fgets(content, 1024, file)){
		token = strtok(content,"\n");
		while(token != NULL){
			if(line == 0){
				char* tokenTemp = (char *) malloc((strlen(token) + 1) * sizeof(char));
				strcpy(tokenTemp, token);
				name = strtok(token, "|");
				while(name != NULL){
					genes++;
					name = strtok(NULL, "|");
				}
				pMatrix = (probMatrix *) malloc(sizeof(probMatrix) + genes * sizeof(char *));
				pMatrix->genes = genes;
				name = strtok(tokenTemp, "|");
				int nameIndex = 0;
				while(name != NULL) {
					pMatrix->names[nameIndex] = (char *) malloc((strlen(name) + 1) * sizeof(char));
					strcpy(pMatrix->names[nameIndex], name);
					name = strtok(NULL, "|");
					nameIndex++;
				}
				pMatrix->probabilityTable = (double **) malloc(pMatrix->genes * sizeof(double *));
				for(int i = 0; i < pMatrix->genes; i++){
					pMatrix->probabilityTable[i] = (double *) malloc(pMatrix->genes * sizeof(double));
				}
				free(tokenTemp);
				line++;
			} else {
				number = strtok(token,"|");
				printf("%s = %f\n", number, strtod(number, NULL));
				
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
	free(token);
	fclose(file);
	return pMatrix;
}

void saveFile(probMatrix *matrix, char *fileName){
	FILE *file = fopen(fileName, "w+");
	if(file == NULL){
		printf("Error writing file");
		exit(1);
	}
	
	for(int i = 0; i < matrix->genes; i++){
		char *gene = "%s,";
		if(i < matrix->genes -1){
			gene = "%s\n";
		}
		fprintf(file, gene, matrix->names[i]);
	}
	for(int i = 0; i < matrix->genes; i++){
		for(int j = 0; j < matrix->genes; j++){
			char *prob = "%lf|";
			if(j == matrix->genes -1){
				prob = "%lf\n";
			}
			fprintf(file, prob, matrix->probabilityTable[i][j]);
		}
	}
	fclose(file);
}
