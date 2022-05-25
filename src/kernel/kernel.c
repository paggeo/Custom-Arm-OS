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

  printk("Initialization \n");
	irq_vector_init();
	printk("Interrupts have been initialized successfully Done\n");
	
	
  printk("Enabling IRQ controllers...\n");
	enable_interrupt_controller();
	printk("IRQ controllers have been enabled \n");
	
  printk("Enabling IRQs...\n");
  enable_irq();
	printk("IRQs have been enabled !\n");
  
  printk("Initializing I2C...\n");
  i2c_init();
  printk("I2C has been enabled !\n");


  char device[DEVICE_LENGTH];
  strcpy(device, "pi3a+");

  console(device);
}
