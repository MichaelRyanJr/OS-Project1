# OS-Project1
CPU Scheduling Algorithm Simulator

To compile & run:
1) g++ src/main.cpp src/pcb.cpp src/queue.cpp src/scheduler.cpp -o scheduler
2) ./scheduler
Note: This was originally coded in C not C++ which is why it looks more like C, luckily the port took minimal effort to accomplish as there were only two sets of errors and both related to memory allocation in queue.cpp

Assumptions:
1) pid array can only store 20 elements, assumption is that any examples wont contain more than 20  processes
2) assumed when q=2 round robin will preempt

Github Project Page: https://github.com/MichaelRyanJr/OS-Project1
