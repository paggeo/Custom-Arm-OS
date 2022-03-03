/*
#include <stddef.h>
#include <stdint.h>
#include "mini_uart.h"
 
//#include <kernel/uart.h>
//#include <kernel/mmio.h>

 
#if defined(__cplusplus)
extern "C" 
#endif
 
void kernel_main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3)
{
	// initialize UART for Raspi2
	uart_init();
	uart_send_string("Hello, kernel World!\r\n");
 
  char values[5];
  values[0] = 'N';
  values[1] = 'K';
  values[2] = 'c';
  values[3] = 'e';
  values[4] = '\n';

  int i = 0;
  for(i=0;i<5;i++){
    uart_send(values[i]);
  }

 uart_send_string(values);

	while (1)
		uart_send(uart_recv());
} 
*/
#include <clib/printf.h>
#include "mini_uart.h"

void kernel_main(void)
{
	uart_init();


	int i;
	init_printf(0, putc);
  printf("Nice\n\0");

	while (1) {
		uart_send(uart_recv());
	}
}

