#include <clib/printf.h>
#include "mini_uart.h"
#include <clib/printk.h>
#include "utils.h"

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
	/* init_printf(0, putc); */
  /* printf("Nice\r\n\0"); */

	while (1) {
		uart_send(uart_recv());
	}
}

