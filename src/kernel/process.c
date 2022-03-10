#include <clib/string.h>
#include <clib/stdlib.h>
#include "utils.h"
#include <clib/printk.h>
#include "timer.h"
#include "entry.h"
#include "peripherals/irq.h"
#include <sched.h>
#include <mini_uart.h>
#include "irq.h"
#include "fork.h"
#include "mm.h"
#include "sys.h"



/* String array, for the message of each process */
static char proc_args[NR_TASKS][10];

/**
 * Dummy function that simulates a process.
 * @param array A char array pointer.
 * @details It just prints the items of its char array.
 */
void process1(char *array)
{
	while (1) {
		for (int i = 0; i < 5; i++) {
			printk("%c", array[i]);
			delay(100000);
		}
	}
}


void create_processes(int proc_num)
{
	/* Get running tasks, for generating pid for each new task in the system */
	int pid = nr_tasks;
	int start_pid = nr_tasks;

	/* Create only a maximum of NR_TASKS */
	for (int i = 0; i < proc_num; i++, pid++) {

		/* Check if processes >= Maximum Total Processes */
		if (pid >= NR_TASKS) {
			printk("Can't create %d process(es)\n", proc_num - (pid - start_pid));
			printk("Total processes must be: 0 < procs < %d \n", NR_TASKS);
			return;
		}

		printk("Forking process %d...", pid);

		strcpy(proc_args[pid], "Hello from proc with pid = ");
		strcat(proc_args[pid], itoa(pid));
		strcat(proc_args[pid], ", ");

        int res = copy_process((unsigned long)&process1, (unsigned long)"12345",0,0);
	    
		if (res != 0) {
			printk("Error while starting process %d\n", pid);
			return;
		}
		printk("Done\n");
	}
}


void kill_processes()
{
	/*
	 * Preemption is disabled for the current task.
	 * We don't want to be rescheduled to a different task
	 * in the middle of killing another task.
	 */
	preempt_disable();

	/* Allocate pointer for the new task */
	struct task_struct *p;

	/*
	 * Iterate over all tasks and try to kill all runing ones.
	 */
	for (int i = 0; i < NR_TASKS; i++) {
		p = task[i];
		/* If it is an allocated task, and not the init task */
		if (p != 0 && i != 0) {
			/* Free allocated memory of task */
            free_page((unsigned long) p);
			/* Decrease number of processes */
			nr_tasks--;
			/* Remove task_struct from task array */
			task[i] = 0;

			printk("Killed task %d, located at %d\n", i, p);
		}
	}

}
void low_priority_process(char *array)
{
	char buf[2] = {0};
  int count = 0;
	while (count < 10){
		for (int i = 0; i < 5; i++){
			buf[0] = array[i];
			call_sys_write(buf);
			delay(1000000);
		}
    count++;
	}
}

void middle_priority_process(char *array)
{
  char buf[2] = {0};

  int count = 0;
	while (count < 10){
		for (int i = 0; i < 5; i++){
			buf[0] = array[i];
			call_sys_write(buf);
			delay(1000000);
		}
    count++;
	}
}

void high_priority_process(char *array)
{
  printk("\nHigh priority process\n");

  char buf[2] = {0};
  sys_change_prior(5);
  int count = 0;
	while (count < 10){
		for (int i = 0; i < 5; i++){
			buf[0] = array[i];
			call_sys_write(buf);
			delay(1000000);
		}
    count++;
	}
  sys_change_prior(0);
  printk("\nEnd of high priority process\n");
}

void user_process(){
	
	printk("\nUser process started \n");
	unsigned long stack = call_sys_malloc();
	if (stack < 0) {
		printk("Error while allocating stack for process 1\n\r");
		return;
	}
	int err = call_sys_clone((unsigned long)&low_priority_process, (unsigned long)"12345", stack);
	if (err < 0){
		printk("Error while clonning process 1\n\r");
		return;
	} 
	stack = call_sys_malloc();
	if (stack < 0) {
		printk("Error while allocating stack for process 1\n\r");
		return;
	}
	err = call_sys_clone((unsigned long)&middle_priority_process, (unsigned long)"abcde", stack);
	if (err < 0){
		printk("Error while clonning process 2\n\r");
		return;
	} 
	stack = call_sys_malloc();
	if (stack < 0) {
		printk("Error while allocating stack for process 3\n\r");
		return;
	}
	err = call_sys_clone((unsigned long)&high_priority_process, (unsigned long)"zqrty", stack);
	if (err < 0){
		printk("Error while clonning process 2\n\r");
		return;
	} 
	call_sys_exit();
}

void kernel_process(){
	printk("\nKernel process started. EL %d\r\n", get_el());
	int err = move_to_user_mode((unsigned long)&user_process);
	if (err < 0){
		printk("Error while moving process to user mode\n\r");
	} 
  disable_timer_irq();
  printk("end of kernel process\n");
}
