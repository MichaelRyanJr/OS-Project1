#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
  int *data;
  int size;
  int capacity;
} Queue;

void initQueue(Queue *q, int capacity);
void freeQueue(Queue *q);
int isEmpty(Queue *q);
void giveQueue(Queue *q, int value);
int takeQueue(Queue *q);
int takeAt(Queue *q, int pos);
int getAt(Queue *q, int pos);

#endif
