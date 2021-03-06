#include "list.h"

// Matrix list

MatrixNode * createnode(probMatrix *matrix){
  MatrixNode * newNode = malloc(sizeof(MatrixNode));
  newNode->matrix = matrix;
  newNode->next = NULL;
  return newNode;
}

MatrixList * emptyMatrixList(){
  MatrixList * list = malloc(sizeof(MatrixList));
  list->head = NULL;
  return list;
}

void display(MatrixList * list) {
  MatrixNode * current = list->head;
  if(list->head == NULL)
    return;
  while(current->next != NULL){
    printMatrix(current->matrix);
    current = current->next;
  }
  printMatrix(current->matrix);
}

void add(probMatrix *matrix, MatrixList *list){
  MatrixNode * current = NULL;
  if(list->head == NULL){
    list->head = createnode(matrix);
  }
  else {
    current = list->head;
    while (current->next!=NULL){
      current = current->next;
    }
    current->next = createnode(matrix);
  }
}

void delete(MatrixNode *node, MatrixList *list){
  MatrixNode *current = list->head;
  MatrixNode *previous = current;
  while(current != NULL){
    if(current == node){
      previous->next = current->next;
      if(current == list->head)
        list->head = current->next;
        destroyMatrix(current->matrix);
      free(current);
      return;
    }
    previous = current;
    current = current->next;
  }
}

void destroy(MatrixList *list){
  MatrixNode * current = list->head;
  MatrixNode * next = current;
  while(current != NULL){
    next = current->next;
    destroyMatrix(current->matrix);
    free(current);
    current = next;
  }
  free(list);
}

// Gene list

GeneList * emptyNodeList(){
  GeneList * list = malloc(sizeof(GeneList));
  list->head = NULL;
  return list;
}

GeneNode * createGeneNode(char *gene, double distance){
  GeneNode * newNode = malloc(sizeof(GeneNode));
  newNode->gene = gene;
  newNode->distance = distance;
  newNode->next = NULL;
  return newNode;
}

void addGene(char *gene, double distance, GeneList *list){
  GeneNode * current = NULL;
  if(list->head == NULL){
    list->head = createGeneNode(gene, distance);
  }
  else {
    current = list->head;
    while (current->next!=NULL){
      current = current->next;
    }
    current->next = createGeneNode(gene, distance);
  }
}

void reverse(GeneList * list){
   GeneNode * reversed = NULL;
   GeneNode * current = list->head;
   GeneNode * temp = NULL;
   while(current != NULL){
     temp = current;
     current = current->next;
     temp->next = reversed;
     reversed = temp;
   }
   list->head = reversed;
 }

void displayGeneList(GeneList *list) {
  GeneNode * current = list->head;
  if(list->head == NULL)
    return;
  while(current->next != NULL){
    printf("-- %f --  %s ", current->distance, current->gene);
    current = current->next;
  }
  printf("-- %f --  %s \n", current->distance, current->gene);
}

void destroyGeneList(GeneList *list){
  GeneNode * current = list->head;
  GeneNode * next = current;
  while(current != NULL){
    next = current->next;
    //free(current->gene);
    free(current);
    current = next;
  }
  free(list);
}


// Value list
ValueList * emptyValueList(){
  ValueList * list = malloc(sizeof(ValueList));
  list->head = NULL;
  return list;
}

ValueNode * createValueNode(char *i, char *j, double value){
  ValueNode * newNode = malloc(sizeof(ValueNode));
  newNode->i = malloc((strlen(i) + 1)  * sizeof(char));
  newNode->j = malloc((strlen(j) + 1)  * sizeof(char));
  strcpy(newNode->i, i);
  strcpy(newNode->j, j);
  newNode->value = value;
  newNode->next = NULL;
  return newNode;
}

void addValue(char *i, char *j, double value, ValueList *list){
  ValueNode *current = NULL;
  if(list->head == NULL){
    list->head = createValueNode(i, j, value);
  }
  else {
    current = list->head;
    while (current->next!=NULL){
      current = current->next;
    }
    current->next = createValueNode(i, j, value);
  }
}

void displayValueList(ValueList *list){
  ValueNode * current = list->head;
  if(list->head == NULL)
    return;
  while(current->next != NULL){
    printf("%s, %s = %f\n", current->i, current->j, current->value);
    current = current->next;
  }
  printf("%s, %s = %f\n", current->i, current->j, current->value);
}


void destroyValueList(ValueList *list){
  ValueNode * current = list->head;
  ValueNode * next = current;
  while(current != NULL){
    next = current->next;
    free(current->i);
    free(current->j);
    free(current);
    current = next;
  }
  free(list);
}



// Map list

MapNode * createMapNode(GeneList *map){
  MapNode * newNode = malloc(sizeof(MapNode));
  newNode->map = map;
  newNode->next = NULL;
  return newNode;
}

MapList * emptyMapList(){
  MapList * list = malloc(sizeof(MapList));
  list->head = NULL;
  return list;
}

void addMap(GeneList *map, MapList *list){
  MapNode * current = NULL;
  if(list->head == NULL){
    list->head = createMapNode(map);
  }
  else {
    current = list->head;
    while (current->next!=NULL){
      current = current->next;
    }
    current->next = createMapNode(map);
  }
}

void displayMapList(MapList *list){
  MapNode * current = list->head;
  if(list->head == NULL)
    return;
  while(current->next != NULL){
    displayGeneList(current->map);
    current = current->next;
  }
  displayGeneList(current->map);
}

void destroyMapList(MapList *list){
  MapNode * current = list->head;
  MapNode * next = current;
  while(current != NULL){
    next = current->next;
    destroyGeneList(current->map);
    free(current);
    current = next;
  }
  free(list);
}
