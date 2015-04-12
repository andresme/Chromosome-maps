#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h> 
#include "main.h"
#include <locale.h>
#define SCALE 1000

GtkWidget *window;
GtkEntry  *path;
GtkWidget *matriz;
GtkTextBuffer *buffer;
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
    
    if(!gtk_builder_add_from_file(builder, "data.glade", &error)) {
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
		path = (GtkEntry *) GTK_WIDGET(gtk_builder_get_object(builder, "path"));
		matriz = GTK_WIDGET(gtk_builder_get_object(builder, "matriz"));
		buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (matriz));
		gtk_text_buffer_set_text (buffer, "G01,G02,G03,G04\n0,0.05,0.07,0.15\n0,0,0.02,0.10\n0,0,0,0.08\n0,0,0,0", -1);
	}

void on_saveFile_clicked(GtkButton *button, gpointer data){
	char *pathFile = save();
	matrix = readFile(pathFile);
}

void on_loadFile_clicked(GtkButton *button, gpointer data){
	char *pathFile = (char *) gtk_entry_get_text(path);
	matrix = readFile(pathFile);
	printMatrix(matrix);
	char *dataFile = dataFromFile(pathFile);
	gtk_text_buffer_set_text (buffer, dataFile, -1);
}

void on_predict_clicked(GtkButton *button, gpointer data){
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
	char *source = NULL;
	FILE *fp = fopen(path, "r");
	if (fp != NULL) {
	    /* Go to the end of the file. */
	    if (fseek(fp, 0L, SEEK_END) == 0) {
	        /* Get the size of the file. */
	        long bufsize = ftell(fp);
	        if (bufsize == -1) { /* Error */ }
	
	        /* Allocate our buffer to that size. */
	        source = malloc(sizeof(char) * (bufsize + 1));
	
	        /* Go back to the start of the file. */
	        if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */ }
	
	        /* Read the entire file into memory. */
	        size_t newLen = fread(source, sizeof(char), bufsize, fp);
	        if (newLen == 0) {
	            fputs("Error reading file", stderr);
	        } else {
	            source[++newLen] = '\0'; /* Just to be safe. */
	        }
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

