#include "clib/printk.h"
#include "utils.h"
#include "timer.h"
#include "irq.h"
#include "sched.h"
#include "fork.h"
#include "mini_uart.h"
#include "sys.h"

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
  printk("End of user processes\n");
	if (err < 0){
		printk("Error while moving process to user mode\n\r");
	} 
}


void kernel_main(void)
{
	uart_init();
  printk("\n\n");
	printk("                  _____ _____ \n");
	printk(" ___ ___ _____   |     |   __|\n");
	printk("| . |  _|     |  |  |  |__   |\n");
	printk("|__,|_| |_|_|_|  |_____|_____|\n");

	printk("\nCustom Arm OS initializing...\n\n");

  printk("\n\tBoard: Raspberry Pi 3\n");
  printk("\tArch: aarch64\n");

  printk("Initializing IRQs...\n");
	irq_vector_init();
	printk("Done\n");
	
  printk("Enabling IRQs...\n");
	timer_init();
	printk("Done\n");
	
  printk("Enabling IRQ controllers...\n");
	enable_interrupt_controller();
	printk("Done\n");
	
  printk("Enabling IRQs...\n");
  enable_irq();
	printk("Done\n");

  

	int res = copy_process(PF_KTHREAD, (unsigned long)&kernel_process, 0, 0);
	if (res < 0) {
		printk("error while starting kernel process");
		return;
	}

	while (1){
		schedule();
	}	
}
