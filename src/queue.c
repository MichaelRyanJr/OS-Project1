#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void initQueue(Queue *q, int capacity){
  q->data = malloc(capacity * sizeof(int));
  q->size = 0;
  q->capacity = capacity;
}


void freeQueue(Queue *q){
  free(q->data);
  q->data = NULL;
  q->size = 0;
  q->capacity = 0;
}


void giveQueue(Queue *q, int value){
  if(q->size != q->capacity){
    q->data[q->size] = value;
    q->size++;
  }
}


int takeQueue(Queue *q){
  if(q->size <= 0){
    return -1;
  }

  
  int value = q->data[0];
  for(int i = 0; i < q->size - 1; i++){
    q->data[i] = q->data[i+1];
  }
  q->size--;
  return value;
}


int takeAt(Queue *q, int pos){
  if(q->size <= pos || pos < 0){
    return -1;
  }

  int value = q->data[pos];
  for(int i = pos; i < q->size - 1; i++){
    q->data[i] = q->data[i+1];
  }
  q->size--;
  return value;
}


int getAt(Queue *q, int pos){
  if(q->size <= pos || pos < 0){
    return -1;
  }

  return q->data[pos];
}





