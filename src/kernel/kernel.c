#include "clib/printk.h"
#include "utils.h"
#include "timer.h"
#include "irq.h"
#include "sched.h"
#include "fork.h"
#include "mini_uart.h"
#include "sys.h"
#include "process.h"
#include "console.h"
#include "clib/string.h"
void kernel_main(void)
{
	uart_init();
  printk("\n\n");
	printk("Greetings !!! this is a custom rasberry pi operating system  created for the course Embedded Systems Design of the NTUA_ \n");
	printk("this is a custom rasberry pi operating system  \n");
	printk("created for the course Embedded Systems Design of the NTUA_ \n\n\n");
	
	printk("Collaborators of this project : \n\n");
	printk("George Pagonis -- 03117030: \n");
	printk("Dimitrios Lampros -- 03117070 : \n");
	printk("Dimitrios Stamatios Bouras -- 03117072: \n");
	
	printk("\n initialization...\n\n");

  printk("\n\tBoard: Raspberry Pi 3 A+ \n");
  //printk("\tArch: aarch64\n");

  printk("Interrupts Initialization \n");
	irq_vector_init();
	printk("Interrupts have been initialized successfully Done\n");
	
  /* printk("Enabling IRQs...\n"); */
	/* timer_init(); */
	/* printk("Done\n"); */
	
  printk("Enabling IRQ controllers...\n");
	enable_interrupt_controller();
	printk("IRQ controllers have been enabled !n");
	
  printk("Enabling IRQs...\n");
  enable_irq();
	printk("IRQs have been enabled !\n");

  

	/* int res = copy_process(PF_KTHREAD, (unsigned long)&kernel_process, 0, 0); */
	/* if (res < 0) { */
	/* 	printk("error while starting kernel process"); */
	/* 	return; */
	/* } */

	printk("Setting up console ..... \n");
	
  char device[DEVICE_LENGTH];
  strcpy(device, "pi-3");
	printk("Console set up successfully  ..... \n");
	
  console(device);
	/* while (1){ */
	/* 	schedule(); */
	/* } */	
}
