#include "pcb.h"
#include <string.h>

void initPCB(PCB *p, char *pid, int arrival, int burst, int priority){
  strcpy(p->pid, pid);
  p->arrivalTime = arrival;
  p->burstTime = burst;
  p->remainingTime = burst;
  p->priority = priority;
  p->startTime = -1;
  p->completionTime = -1;
  p->state = NEW;
}
