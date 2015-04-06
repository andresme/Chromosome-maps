#ifndef _FILE_H_

#define _FILE_H_

#include "utils.h"


probMatrix* readFile(char* fileName);
void saveFile(probMatrix *matrix, char *fileName);
#endif
