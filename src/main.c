#include <stdio.h>
#include "pcb.h"

int main(void){
  FILE *inFile;
  FILE *outFile;

  PCB processes[100];
  int count = 0;

  char header[100];
  char pid[20];
  int arrival;
  int burst;
  int priority;

  inFile = fopen("input.txt", "r");

  fgets(header, sizeof(header), inFile);
  while(fscanf(inFile, "%s %d %d %d", pid, &arrival, &burst, &priority) == 4){
    initPCB(&processes[count], pid, arrival, burst, priority);
    count++;
  }
  fclose(inFile);

  outFile = fopen("output_test.txt", "w");

  fprintf(outFile, "Test of printPCB():\n");
  for(int i = 0; i < count; i++){
    printPCB(outFile, &processes[i]);
  }
  fclose(outFile);

  return 0;
}
