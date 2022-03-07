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

	int i;
  printk("\narmOS initializing...\n");
  printk("Integer = %d\n",5);
  printk("Character = %c\n",'t');
  printk("String = %s\n" , "nice");
  printk("Hex = %x\n" , 12);

  int el = get_el();
	printk("Exception level: %d \r\n", el);
  irq_vector_init();
	timer_init();
	enable_interrupt_controller();
	enable_irq();

  int res = copy_process((unsigned long)&process, (unsigned long)"12345");
	if (res != 0) {
		printk("error while starting process 1");
		return;
	}
	res = copy_process((unsigned long)&process, (unsigned long)"abcde");
	if (res != 0) {
		printk("error while starting process 2");
		return;
	}

	while (1){
		schedule();
	}

}
