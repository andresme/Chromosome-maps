#ifndef _MAIN_H_

#define _MAIN_H_

#include "gnuplot_i.h"
#include "utils.h"
#include "file.h"
#include "list.h"
#include "structs.h"


void plotMaps(MapList *list);
char* dataFromFile(char* path);
void getGtkWidgets(GtkBuilder *builder);
char * save();

#endif
