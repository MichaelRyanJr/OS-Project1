#include <stdio.h>
#include "pcb.h"
#include "scheduler.h"

//Copies processes array
void copyProcesses(PCB dest[], PCB src[], int count){
  for(int i = 0; i < count; i++){
    dest[i] = src[i];
  }
}

int main(void){
  FILE *inFile;
  FILE *outFile;

  PCB originalProcesses[100];
  PCB workingProcesses[100];
  int count = 0;

  char header[100];
  char pid[20];
  int arrival;
  int burst;
  int priority;

  inFile = fopen("input.txt", "r");

  fgets(header, sizeof(header), inFile);
  while(fscanf(inFile, "%s %d %d %d", pid, &arrival, &burst, &priority) == 4){
    initPCB(&originalProcesses[count], pid, arrival, burst, priority);
    count++;
  }
  fclose(inFile);

  ///// FCFS /////
  copyProcesses(workingProcesses, originalProcesses, count);
  outFile = fopen("output_fcfs.txt", "w");
  runFCFS(outFile, workingProcesses, count);
  fclose(outFile);

  ///// Priority /////
  copyProcesses(workingProcesses, originalProcesses, count);
  outFile = fopen("output_priority.txt", "w");
  runPriority(outFile, workingProcesses, count);
  fclose(outFile);

  ///// SRTF /////
  copyProcesses(workingProcesses, originalProcesses, count);
  outFile = fopen("output_srtf.txt", "w");
  runSRTF(outFile, workingProcesses, count);
  fclose(outFile);
  
  return 0;
}
