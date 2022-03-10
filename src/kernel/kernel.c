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
	
  /* printk("Enabling IRQs...\n"); */
	/* timer_init(); */
	/* printk("Done\n"); */
	
  printk("Enabling IRQ controllers...\n");
	enable_interrupt_controller();
	printk("Done\n");
	
  printk("Enabling IRQs...\n");
  enable_irq();
	printk("Done\n");

  

	/* int res = copy_process(PF_KTHREAD, (unsigned long)&kernel_process, 0, 0); */
	/* if (res < 0) { */
	/* 	printk("error while starting kernel process"); */
	/* 	return; */
	/* } */
  char device[DEVICE_LENGTH];
  strcpy(device, "pi-3");

  console(device);
	/* while (1){ */
	/* 	schedule(); */
	/* } */	
}
