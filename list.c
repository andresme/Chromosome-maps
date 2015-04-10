#include "list.h"

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
    free(current);
    current = next;
  }
  free(list);
}

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

void displayGeneList(GeneList *list) {
  GeneNode * current = list->head;
  if(list->head == NULL) 
    return;
  while(current->next != NULL){
    printf("%s -", current->gene);
    current = current->next;
  }
  printf("%s -", current->gene);
}

void destroyGeneList(GeneList *list){
  GeneNode * current = list->head;
  GeneNode * next = current;
  while(current != NULL){
    next = current->next;
    free(current);
    current = next;
  }
  free(list);
}
