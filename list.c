#include "list.h"

MatrixNode * createnode(probMatrix *matrix);

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

// void reverse(List * list){
//   Node * reversed = NULL;
//   Node * current = list->head;
//   Node * temp = NULL;
//   while(current != NULL){
//     temp = current;
//     current = current->next;
//     temp->next = reversed;
//     reversed = temp;
//   }
//   list->head = reversed;
// }

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
