#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdio.h>
#include "pcb.h"
#include "queue.h"

void runFCFS(FILE *outFile, PCB processes[], int count);
void runPriority(FILE *outFile, PCB processes[], int count);
void runSRTF(FILE *outFile, PCB processes[], int count);
void runRR(FILE *outFile, PCB processes[], int count);
int allTerminated(PCB processes[], int count);
void printTimeStep(FILE *outFile, int time, PCB processes[], int runningIndex, Queue *readyQueue);
void printGanttChart(FILE *outFile, PCB processes[], int gantt[], int ganttLength);

#endif
