#include <stdint.h>
#include <console.h>
#include <clib/printk.h>
#include <clib/string.h>
#include "utils.h"
#include "timer.h"
#include "irq.h"
#include "sched.h"
#include "fork.h"
#include "mini_uart.h"
#include "sys.h"
#include "process.h"

char *console_init(char *device)
{
	static char prompt[PROMPT_LENGTH];

	/* Create prompt */
	strcpy(prompt, "root@");
	strcat(prompt, device);
	strcat(prompt, "#");

	return prompt;
}

int console_get_cmd(char *input)
{
	if (strcmp(input, "help") == 0)
		return cmd_help;
  else if (strcmp(input, "schedule") == 0)
		return cmd_schedule;
  else if (strcmp(input, "cat_1") == 0)
		return cmd_cat_1;
  else if (strcmp(input, "cat_2") == 0)
		return cmd_cat_2;
  else if (strcmp(input, "i2c") == 0)
		return cmd_i2c;
	else
		return -1;
}

void console(char *device)
{
	char *input;
	char *args;
	char *prompt;
	int msec, count, pin_num, proc_num;

	/* Get prompt */
	prompt = console_init(device);

	/* Print console info */
	printk("\n");
	printk("This is a minimal console, type 'help' to see the available commands. (Maximum Input Length: %d)\n", MAX_INPUT_LENGTH);

	/* Main functionality */
	while (1) {
		/* Print prompt */
		printk("%s ", prompt);
		/* Read from serial */
		input = uart_recv_string();
		printk("\n");
    command cmd = console_get_cmd(input);

		switch (cmd) {
      case cmd_help:
        console_help();
        break;
      case cmd_schedule:
        console_schedule();
        break;
      case cmd_cat_1:
        console_cat_1();
        break;
      case cmd_cat_2:
        console_cat_2();
        break;
      case cmd_i2c:
        console_i2c();
        break;
      default:
        printk("%s: command not found\n", input);
        printk("type 'help' to see the available commands\n");
        break;
		  }
  }
}

void console_schedule(){
  printk("\nStart scheduling\n");
  printk("Enabling IRQs...\n");
	timer_init();
	printk("Done\n");
  int res = copy_process(PF_KTHREAD, (unsigned long)&kernel_process, 0, 0);
	if (res < 0) {
		printk("error while starting kernel process");
		return;
	}
  int counter = 0;
  while (counter<3){
		schedule();
    counter++;
	}
  disable_timer_irq();
  kill_processes();
  printk("\nEnd of schedule\n");
};

void console_cat_1(){
	timer_init();
  int res = copy_process(PF_KTHREAD, (unsigned long)&kernel_process_cat_1, 0, 0);
	if (res < 0) {
		printk("error while starting kernel process");
		return;
	}
  int counter = 0;
  while (counter<100){
		schedule();
    counter++;
	}
  disable_timer_irq();
  kill_processes();
};

void console_cat_2(){
	timer_init();
  int res = copy_process(PF_KTHREAD, (unsigned long)&kernel_process_cat_2, 0, 0);
	if (res < 0) {
		printk("error while starting kernel process");
		return;
	}
  int counter = 0;
  while (counter<100){
		schedule();
    counter++;
	}
  disable_timer_irq();
  kill_processes();
};

void console_help()
{
	printk("Available commands:\n");
	printk("    help:\n");
	printk("        Prints available commands to the console.\n");
	printk("    schedule:\n");
	printk("        Demo for scheduling.\n");
	printk("    cat_1:\n");
	printk("        System call for cat1.\n");
	printk("    cat_2:\n");
	printk("        System call for cat2.\n");
	printk("    i2c:\n");
	printk("        System call for i2c.\n");
}

void console_i2c(){

  int ret_val;

	for (int i=0; i<10; i++) {
        char buffer[10];
        ret_val=i2c_recv(21, buffer, 9);
        buffer[9] = 0;

        if (ret_val==0)
	{

       
        printk("Received: %s\n", buffer);


	}
	else 
	{

		printk("mision failed 1, we'll get them next time error: %d \n",ret_val);
	}
       

        delay(500);
    }


	for (unsigned char d=0; d<20; d++) {
        ret_val = i2c_send(21, &d, 1);

        delay(500);

      if (ret_val==0)
	{

        printk("Sent: %d\n", d);


	}
	else 
	{

		printk("mision failed 2, we'll get them next time error: %d \n",ret_val);
	}
       
    }

     char *msg = "Hello Slave Device";
    i2c_send(21, msg, 18);


    printk("DONE!\n");

}
