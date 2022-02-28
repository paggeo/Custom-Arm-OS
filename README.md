# Custom-Arm-OS


## Scheduling 
- Task (stuct)
  - state of task
  - counter
  - priority
  - cpu\_context

- Cpu\_context
  - Replace register (done in asm)
    - we save 19\-\-28 as callee-saved registers, LR, FP,SP,PC as special registers. [Documentation](https://developer.arm.com/documentation/ihi0055/d/)

![Screenshot](./images/general_registers.png)
  
- Create 3 tables with specific size (could be done with list but has to create malloc). Create pointers : head, curr,tail and a counter = size.
  - Head : to know the starting position of the table
  - Curr : the next to be taken by scheduler
  - Tail : the last , if someone comes goes here. 


- Priorities: 
  - High Priority (preemptive scheduling: stop everything and run this)
  - Middle Priotity (non-preemptive scheduling: when a process is finished)
  - Low Priotity 


- Forking|Creating tasks : fork(name,priority)
- Task 
- Print tasks : Every time a task is added, finished, interrupted|context\_switching print all tasks in beautifull ways.
