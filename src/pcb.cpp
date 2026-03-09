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

const char *stateToString(ProcessState state){
  if(state == NEW){
    return "NEW";
  }
  else if(state == READY){
    return "READY";
  }
  else if(state == RUNNING){
    return "RUNNING";
  }
  else if(state == TERMINATED){
    return "TERMINATED";
  }

  return "ERROR";
}

void printPCB(FILE *fp, PCB *p){
  fprintf(fp, "PID=%s Arr=%d Burst=%d Rem=%d Prio=%d State=%s\n", p->pid, p->arrivalTime, p->burstTime, p->remainingTime, p->priority, stateToString(p->state));
}
