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
	printk("Greetings !!!\n"); 
	printk("This is a custom rasberry pi operating system  \n");
	printk("Created for the course Embedded Systems Design of the NTUA_ \n\n\n");
	
	printk("Collaborators of this project : \n\n");
	printk("George Pagonis -- 03117030: \n");
	printk("Dimitrios Lampros -- 03117070 : \n");
	printk("Dimitrios Stamatios Bouras -- 03117072: \n");
	
	printk("\n initialization...\n\n");

  printk("\n\tBoard: Raspberry Pi 3 A+ \n");
  //printk("\tArch: aarch64\n");

  printk("\t\tInterrupts Initialization \n");
	irq_vector_init();
	printk("\t\tInterrupts have been initialized successfully Done\n");
	
  /* printk("Enabling IRQs...\n"); */
	/* timer_init(); */
	/* printk("Done\n"); */
	
  printk("\t\tEnabling IRQ controllers...\n");
	enable_interrupt_controller();
	printk("\t\tIRQ controllers have been enabled !n");
	
  printk("\t\tEnabling IRQs...\n");
  enable_irq();
	printk("\t\tIRQs have been enabled !\n");
  
  printk("\t\tInitializing I2C...\n");
  i2c_init();
  printk("\t\tI2C has been enabled !\n");


	/* int res = copy_process(PF_KTHREAD, (unsigned long)&kernel_process, 0, 0); */
	/* if (res < 0) { */
	/* 	printk("error while starting kernel process"); */
	/* 	return; */
	/* } */
  char device[DEVICE_LENGTH];
  strcpy(device, "pi3a+");

  console(device);
	/* while (1){ */
	/* 	schedule(); */
	/* } */	
}
