# OS-Project1
CPU Scheduling Algorithm Simulator

To compile & run:
1) gcc src/main.c src/pcb.c src/queue.c src/scheduler.c -o scheduler
2) ./scheduler
Note: Uses gcc as an alternative to g++, I realized that you specified g++ (not gcc like I initially thought I read) in the example after I completed the assignment.

Assumptions:
1) pid array can only store 20 elements, assumption is that any examples wont contain more than 20  processes
2) assumed when q=2 round robin will preempt
