#include <clib/printf.h>
#include "mini_uart.h"
#include <clib/printk.h>
#include "utils.h"
#include "irq.h"
#include "timer.h"
#include "fork.h"
#include "sched.h"

void process(char *array)
{
	while (1){
		for (int i = 0; i < 5; i++){
			uart_send(array[i]);
			delay(100000);
		}
	}
}


void kernel_main(void)
{
	

  


	uart_init();
	//init_printf(0, putc);
	printk("\narmOS initializing...\n");
  printk("Integer = %d\n",5);
  printk("Character = %c\n",'t');
  printk("String = %s\n" , "nice");
  printk("Hex = %x\n" , 12);

	irq_vector_init();
	timer_init();
	enable_interrupt_controller();
	enable_irq();
	printk("before first copy\r\n");
	int res = copy_process((unsigned long)&process, (unsigned long)"12345");
	printk("i havee copied n1\r\n");
	if (res != 0) {
		printf("error while starting process 1");
		return;
	}
	res = copy_process((unsigned long)&process, (unsigned long)"abcde");
	printk("i have copied n2\r\n");
	if (res != 0) {
		printf("error while starting process 2");
		return;
	}

	while (1){
		schedule();
	}	
}

