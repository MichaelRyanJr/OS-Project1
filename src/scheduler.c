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
  fprintf(outFile, "\nTime %d:\n", time);

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


void printGanttChart(FILE *outFile, PCB processes[], int gantt[], int ganttLength){
  fprintf(outFile, "\nGantt Chart:\n");

  for(int i = 0; i < ganttLength; i++){
    if(gantt[i] == -1){
      fprintf(outFile, "| IDLE ");
    }
    else {
      fprintf(outFile, "| %s ", processes[gantt[i]].pid);
    }
  }

  fprintf(outFile, "|\n");

  for(int i = 0; i <= ganttLength; i++){
    fprintf(outFile, "%d    ", i);
  }
  fprintf(outFile, "\n");
}


void runFCFS(FILE *outFile, PCB processes[], int count){
  Queue readyQueue;
  int time = 0;
  int runningIndex = -1; //-1 indicates idle
  int gantt[1000];
  int ganttLength = 0;

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

    //Record running processes for gantt chart
    gantt[ganttLength] = runningIndex;
    ganttLength++;
    
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

  printGanttChart(outFile, processes, gantt, ganttLength);
  freeQueue(&readyQueue);
}


void runPriority(FILE *outFile, PCB processes[], int count){
  Queue readyQueue;
  int time = 0;
  int runningIndex = -1; //-1 indicates idle
  int gantt[1000];
  int ganttLength = 0;

  initQueue(&readyQueue, count);

  while(allTerminated(processes, count) == 0){
    for(int i = 0; i < count; i++){
      if(processes[i].state == NEW && processes[i].arrivalTime == time){
        processes[i].state = READY;
        giveQueue(&readyQueue, i);
      }
    }

    //if CPU not running and readyQueue is not empty, execute next process according to highest priority(1 = Highest Priority)
    if(isEmpty(&readyQueue) == 0 && runningIndex == -1){
      int bestQueuePos = 0;
      int bestProcessIndex = getAt(&readyQueue, 0);
      int bestPriority = processes[bestProcessIndex].priority;
      
      for(int i = 1; i < readyQueue.size; i++){
        int processIndex = getAt(&readyQueue, i);
        int currentPriority = processes[processIndex].priority;
        //finding index of highest priority in readyQueue
        if(currentPriority < bestPriority){
          bestPriority = currentPriority;
          bestQueuePos = i;
        }
      }
      runningIndex = takeAt(&readyQueue, bestQueuePos); //converting Queue index of best priority to processes index
      processes[runningIndex].state = RUNNING;
      
      if(processes[runningIndex].startTime == -1){
        processes[runningIndex].startTime = time;
      }
    }
     //decrease runningTime if there is a running process
    if(runningIndex != -1){
      processes[runningIndex].remainingTime--;
    }

    //Record running processes for gantt chart
    gantt[ganttLength] = runningIndex;
    ganttLength++;
    
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

  printGanttChart(outFile, processes, gantt, ganttLength);
  freeQueue(&readyQueue);
}


void runSRTF(FILE *outFile, PCB processes[], int count){
  Queue readyQueue;
  int time = 0;
  int runningIndex = -1; //-1 indicates idle
  int gantt[1000];
  int ganttLength = 0;

  initQueue(&readyQueue, count);
  //while all any processes are not terminated, run selection logic
  while(allTerminated(processes, count) == 0){
    for(int i = 0; i < count; i++){
      if(processes[i].state == NEW && processes[i].arrivalTime == time){
        processes[i].state = READY;
        giveQueue(&readyQueue, i);
      }
    }
    //if something is in ready queue and CPU is idle, look for new process (non preemptive selection logic)
    if(isEmpty(&readyQueue) == 0 && runningIndex == -1){
      int bestQueuePos = 0;
      int bestProcessIndex = getAt(&readyQueue, 0);
      int bestRemainingTime = processes[bestProcessIndex].remainingTime;
      //searching for shortest remaining time
      for(int i = 1; i < readyQueue.size; i++){
        int processIndex = getAt(&readyQueue, i);
        int currentRemainingTime = processes[processIndex].remainingTime;
        //if current elements remaining time is shorter, assign it as best fit
        if(currentRemainingTime < bestRemainingTime){ 
          bestRemainingTime = currentRemainingTime;
          bestQueuePos = i;
        }
      }
      runningIndex = takeAt(&readyQueue, bestQueuePos);
      processes[runningIndex].state = RUNNING;
      //if first run, set start time
      if(processes[runningIndex].startTime == -1){
        processes[runningIndex].startTime = time;
      }
    }
    //if queue not empty and something is alredy running, check if running process has SRT, if not, preempt with SRT (preemptive logic)
    if(isEmpty(&readyQueue) == 0 && runningIndex != -1){
      int runningRemainingTime = processes[runningIndex].remainingTime;
      int queueSRTIndex = 0;
      int processIndex = getAt(&readyQueue, 0);
      int queueSRT = processes[processIndex].remainingTime;
      int currentRemainingTime;
      //check current RT against the rest
      for(int i = 1; i < readyQueue.size; i++){
        processIndex = getAt(&readyQueue, i);
        currentRemainingTime = processes[processIndex].remainingTime;
        //check if shorter remaining time found
        if(currentRemainingTime < queueSRT){
          queueSRT = currentRemainingTime;
          queueSRTIndex = i;
        }
      }
      //check if shortest remaining time in queue is shorter than current process, if yes, then swap
      if(queueSRT < runningRemainingTime){
        processes[runningIndex].state = READY;
        giveQueue(&readyQueue, runningIndex);
        
        runningIndex = takeAt(&readyQueue, queueSRTIndex);
        processes[runningIndex].state = RUNNING;
        //Check if this is the new processes first time running
        if(processes[runningIndex].startTime == -1){
          processes[runningIndex].startTime = time;
        }
      }
    }
    
    //if a process is running, decrement its remaining time
    if(runningIndex != -1){
      processes[runningIndex].remainingTime--;
    }
    //Record each step in an array for gantt chart
    gantt[ganttLength] = runningIndex;
    ganttLength++;
    //write time step to output file
    printTimeStep(outFile, time, processes, runningIndex, &readyQueue);
    //update processes data if execution is completed
    if(runningIndex != -1 && processes[runningIndex].remainingTime <= 0){
      processes[runningIndex].completionTime = time + 1;
      processes[runningIndex].state = TERMINATED;
      runningIndex = -1;
    }
    //update current time step
    time++;
  }
  //print gantt chart once all processes terminated
  printGanttChart(outFile, processes, gantt, ganttLength);
  freeQueue(&readyQueue);
}




