#ifndef PCB_H
#define PCB_H
#include <stdio.h>


typedef enum {
  NEW,
  READY,
  RUNNING,
  TERMINATED
} ProcessState;

typedef struct {
  char pid[20];
  int arrivalTime;
  int burstTime;
  int remainingTime;
  int priority;
  int startTime;
  int completionTime;
  ProcessState state;
} PCB;

void initPCB(PCB *p, char *pid, int arrival, int burst, int priority);
const char *stateToString(ProcessState state);
void printPCB(FILE *fp, PCB *p);

#endif
