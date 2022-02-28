#include <stddef.h>
#include <stdint.h>
 
#include <kernel/uart.h>
#include <kernel/mmio.h>
#include <kernel/console.h>

#include <clib/printf.h>
#include <clib/string.h>


 
#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
 
void kernel_main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3)
{
	// initialize UART for Raspi2
	uart_init(3);
	uart_puts("Hello, kernel World!\r\n");
 
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


  init_printf(0, putc);
  printf("Integer: %d, Char: %c, \nString : %s, Hex: 0x%X \n", 2, 'a',"nice",10);
  char device[DEVICE_LENGTH];
  strcpy(device, "pi-3");
	printf("\n\tBoard: Raspberry Pi 3\n");

	while (1)
		console(device);
} 
