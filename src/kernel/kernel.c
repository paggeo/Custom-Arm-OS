#include <stddef.h>
#include <stdint.h>

#include <kernel/uart.h>
#include <kernel/mmio.h>
#include <kernel/console.h>

#include <clib/printf.h>
#include <clib/string.h>

#include <kernel/utils.h>
#include <arm/timer.h>
#include <arm/irq.h>
#include <arm/fork.h>
#include <kernel/sched.h>


 
#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
 
/*void kernel_main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3)
{
	// initialize UART for Raspi2
	uart_init(3);
	uart_puts("Hello, kernel World!\r\n");
  init_printf(0, putc);
  char values[5];
  values[0] = 'N';
  values[1] = 'i';
  values[2] = 'c';
  values[3] = 'e';
  values[4] = '\n';

  
  int i = 0;
  for(i=0;i<5;i++){
    uart_putc(values[i]);
  }
  uart_puts(values);

  int el = get_el();
	printf("Exception level: %d \r\n", el);

  irq_vector_init();
	timer_init();
	enable_interrupt_controller();
	enable_irq();
  
  printf("Integer: %d, Char: %c, \nString : %s, Hex: 0x%X \n", 2, 'a',"nice",10);
  char device[DEVICE_LENGTH];
  strcpy(device, "pi-3");
	printf("\n\tBoard: Raspberry Pi 3\n");

	while (1)
		console(device);
} 
*/
void process(char *array)
{
	while (1){
		for (int i = 0; i < 5; i++){
			uart_puts(array[i]);
			delay(100000);
		}
	}
}

void kernel_main(void)
{
	uart_init(3);
	init_printf(0, putc);
	irq_vector_init();
	timer_init();
	enable_interrupt_controller();
	enable_irq();

	int res = copy_process((unsigned long)&process, (unsigned long)"12345");
	if (res != 0) {
		printf("error while starting process 1");
		return;
	}
	res = copy_process((unsigned long)&process, (unsigned long)"abcde");
	if (res != 0) {
		printf("error while starting process 2");
		return;
	}

	while (1){
		schedule();
	}	
}
/*
void kernel_main(void)
{
	uart_init(3);
	init_printf(0, putc);
	irq_vector_init();
	timer_init();
	enable_interrupt_controller();
	enable_irq();

	while (1){
		uart_puts(uart_gets());
	}	
}*/