#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h> 
#include "main.h"
#include <locale.h>
#define SCALE 1000
#define MAXBUFLEN 1000000

GtkWidget *window;
GtkEntry  *gen1, *gen2;
GtkWidget *matriz, *results;
GtkTextBuffer *buffer, *bufferResults;
GtkBuilder *builder;
probMatrix *matrix;

int main(int argc, char *argv[]) {
	matrix = readFile(argv[1]);
	
	//printMatrix(matrix);
	
	MatrixList *possibles = possibleNumber(matrix);
	MapList *maps = calculatePossibleMaps(possibles);
	displayMapList(maps);
	plotMaps(maps);
	
	//displayMapList(maps);
	destroyMatrix(matrix);
	destroy(possibles);
	destroyMapList(maps);
	
	
	GError *error = NULL;
	gtk_init(&argc, &argv);
	
    builder = gtk_builder_new();
    
    if(!gtk_builder_add_from_file(builder, "mapper_gui.glade", &error)) {
		g_warning("%s", error->message);
		g_free(error);
		return(1);
	}
   	getGtkWidgets(builder);
	gtk_builder_connect_signals(builder, NULL);
	g_object_unref(G_OBJECT(builder));
	gtk_widget_show(window);
	setlocale (LC_ALL,"C");
	gtk_main();

	
	
	return 0;
}

void getGtkWidgets(GtkBuilder *builder){
		window = GTK_WIDGET(gtk_builder_get_object(builder, "data"));
		gen1 = (GtkEntry *) GTK_WIDGET(gtk_builder_get_object(builder, "gen1"));
		gen2 = (GtkEntry *) GTK_WIDGET(gtk_builder_get_object(builder, "gen2"));
		matriz = GTK_WIDGET(gtk_builder_get_object(builder, "matriz"));
		buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (matriz));
		results = GTK_WIDGET(gtk_builder_get_object(builder, "results"));
		bufferResults = gtk_text_view_get_buffer (GTK_TEXT_VIEW (results));
		gtk_text_buffer_set_text (buffer, "G01,G02,G03,G04\n0,0.05,0.07,0.15\n0,0,0.02,0.10\n0,0,0,0.08\n0,0,0,0", -1);
	}

void on_saveFile_clicked(GtkButton *button, gpointer data){
	char *pathFile = save();
	matrix = readFile(pathFile);
}

void on_loadFile_clicked(GtkButton *button, gpointer data){
	GtkWidget *dialog;
	char *filename;
    dialog = gtk_file_chooser_dialog_new ("Cargar Archivo ",
                      NULL,
                      GTK_FILE_CHOOSER_ACTION_SAVE,
                      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                      NULL);
    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT){
		gboolean result;
		GError *err = NULL;
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		printf("%s\n", filename);
		matrix = readFile(filename);
		printMatrix(matrix);
		char *dataFile = dataFromFile(filename);
		gtk_text_buffer_set_text (buffer, dataFile, -1);
		}
	gtk_widget_destroy (dialog);
}

void on_predict_clicked(GtkButton *button, gpointer data){
	GtkTextIter start, end;
	char * algo_magico = "%s -> %s = %1.4f\n";
	char *textGen1 = (char *) gtk_entry_get_text(gen1);
	char *textGen2 = (char *) gtk_entry_get_text(gen2);
	ValueList* list = predictCrossOver(matrix, textGen1, textGen2);
	ValueNode* current = list->head;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (results);
	gtk_text_buffer_set_text (buffer, "\0", -1);
	while(current != NULL){
		buffer = gtk_text_view_get_buffer(results);
		gtk_text_buffer_get_bounds(buffer, &start, &end);
		int size = strlen(current->i)+strlen(current->j)+14;
		char * possible = malloc(size*sizeof(char));
		sprintf(possible, algo_magico, current->i, current->j, current->value);
		gtk_text_buffer_insert (buffer, &end, possible, -1);
		current = current->next;
	}
	destroyValueList(list);
}

void on_generate_clicked(GtkButton *button, gpointer data){
	char *filename;
	gboolean result;
	GError *err = NULL;
	filename = "temp.txt";
	GtkTextIter start, end;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (matriz);
	gchar *text;
	gtk_text_buffer_get_bounds (buffer, &start, &end);
	text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
	result = g_file_set_contents (filename, text, -1, &err);
	
	matrix = readFile(filename);
	printMatrix(matrix);
	MatrixList *possibles = possibleNumber(matrix);
	MapList *maps = calculatePossibleMaps(possibles);
	displayMapList(maps);
	plotMaps(maps);
	//destroy(possibles);
	//destroyMapList(maps);
	
    //while(1){
	 	//tiene que seguir corriendo para poder hacer zoom/pan
	// 	printf(" ");
	//};
}


char * save(){   
	GtkWidget *dialog;
	char *filename;
    dialog = gtk_file_chooser_dialog_new ("Guardar Archivo ",
                      NULL,
                      GTK_FILE_CHOOSER_ACTION_SAVE,
                      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                      GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
                      NULL);
    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT){
		
		gboolean result;
		GError *err = NULL;
		filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		GtkTextIter start, end;
		GtkTextBuffer *buffer = gtk_text_view_get_buffer (matriz);
		gchar *text;
		gtk_text_buffer_get_bounds (buffer, &start, &end);
		text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
		//printf("%s\n", text);
/* set the contents of the file to the text from the buffer */
		if (filename != NULL)        
			result = g_file_set_contents (filename, text, -1, &err);
		else
			result = g_file_set_contents (filename, text, -1, &err);

		if (result == FALSE){
    /* error saving file, show message to user */}        
		g_free (text); 
	}
    gtk_widget_destroy (dialog);
    
    return filename;
}

char* dataFromFile(char* path){
	char source[MAXBUFLEN + 1];
	FILE *fp = fopen(path, "r");
	if (fp != NULL) {
		size_t newLen = fread(source, sizeof(char), MAXBUFLEN, fp);
		if (newLen == 0) {
			fputs("Error reading file", stderr);
		} else {
			source[++newLen] = '\0'; /* Just to be safe. */
		}

		fclose(fp);
	}
	return source;
}

int GetNumberOfDigits (int i){
    int digits = 0; do { i /= 10; digits++; } while (i != 0);
    return digits;
}


void plotMaps(MapList *list){
	gnuplot_ctrl* h1;
	h1 = gnuplot_init();
	
	MapNode *current = list->head;
	char *cmd = "%1.4f title 'map %d', \\";
	char *pattern = "%1.4f title 'map %d'";
	char *label = "set label '%s' at %1.4f,%1.4f";
	int i = 0;
	
	if(current != NULL){
		gnuplot_cmd(h1, "set xrange[0:0.5]");
		gnuplot_cmd(h1, "set yrange[0:0.010]");
		gnuplot_cmd(h1, "plot \\");
	} else {
		printf("No maps found\n");
		return;
	}
	while(current->next != NULL){
		int digits = GetNumberOfDigits(i);
		char *currentCmd = malloc((digits + 23) * sizeof(char));
		sprintf(currentCmd, cmd, ((double)i)/SCALE, i);
		printf("%s\n", currentCmd);
		gnuplot_cmd(h1, currentCmd);
		i++;
		current = current->next;
		free(currentCmd);
	}
	if(i == 0){
		gnuplot_cmd(h1, "0 title 'map 0'");
	} else {
		int digits = GetNumberOfDigits(i);
		char *lastCmd = malloc((digits + 19) * sizeof(char));
		sprintf(lastCmd, pattern, ((double)i)/SCALE, i);
		//printf("%s\n", lastCmd);
		gnuplot_cmd(h1, lastCmd);
		free(lastCmd);
	}
	
	current = list->head;
	i = 0;
	while(current != NULL){
		double value = 0.0;
		GeneNode *node = current->map->head;
		
		while(node != NULL){
			int digits = GetNumberOfDigits(i);
			char *labelCmd = malloc((24 + strlen(node->gene)) * sizeof(char));
			value = value + node->distance;
			sprintf(labelCmd, label, node->gene, value, ((double)i)/SCALE);
			//printf("%s\n", labelCmd);
			gnuplot_cmd(h1, labelCmd);
			node = node->next;
			free(labelCmd);
		}
		current = current->next;
		i++;
	}
}

