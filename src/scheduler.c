#include "scheduler.h"
#include <stdio.h>

//returns 1 if all processes terminated
int allTerminated(PCB processes[], int count){
  for(int i = 0; i < count; i++){
    if(processes[i].state != TERMINATED){
      return 0;
    }
  }
  return 1;
}


void printTimeStep(FILE *outFile, int time, PCB processes[], int runningIndex, Queue *readyQueue){
  fprintf(outFile, "Time %d:\n", time);

  //if runningIndex == -1, CPU idle
  if(runningIndex == -1){
    fprintf(outFile, "RUNNING: IDLE\n");
  }
  else{
    fprintf(outFile, "RUNNING:\n");
    printPCB(outFile, &processes[runningIndex]);
  }

  fprintf(outFile, "READY:\n");
  for(int i = 0; i < readyQueue->size; i++){
    printPCB(outFile, &processes[getAt(readyQueue, i)]);
  }
}


void runFCFS(FILE *outFile, PCB processes[], int count){
  Queue readyQueue;
  int time = 0;
  int runningIndex = -1; //-1 indicates idle

  initQueue(&readyQueue, count);

  //scheduling behaviour loops until all processes terminated, main shceduler logic here
  while(allTerminated(processes, count) == 0){
    //Admit new arrivals if arrivalTime == NEW and its state is NEW
    for(int i = 0; i < count; i++){
      if(processes[i].state == NEW && processes[i].arrivalTime == time){
        processes[i].state = READY;
        giveQueue(&readyQueue, i);
      }
    }
    //if CPU not running and readyQueue is not empty, execute next process
    if(isEmpty(&readyQueue) == 0 && runningIndex == -1){
      runningIndex = takeQueue(&readyQueue);
      processes[runningIndex].state = RUNNING;

      if(processes[runningIndex].startTime == -1){
        processes[runningIndex].startTime = time;
      }
    }
    //decrease runningTime if there is a running process
    if(runningIndex != -1){
      processes[runningIndex].remainingTime--;
    }
    
    printTimeStep(outFile, time, processes, runningIndex, &readyQueue);
    //update process data if process has finished execution
    if(runningIndex != -1 && processes[runningIndex].remainingTime <= 0){
      processes[runningIndex].completionTime = time + 1;
      processes[runningIndex].state = TERMINATED;
      runningIndex = -1;
    }
    //increment time before next loop
    time++;
  }

  freeQueue(&readyQueue);
}





