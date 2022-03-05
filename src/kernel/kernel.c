#include <clib/printf.h>
#include "mini_uart.h"
#include <clib/printk.h>
#include "utils.h"
void kernel_main(void)
{
	uart_init();

	//int i;
  printk("\narmOS initializing...\n");
  printk("Integer = %d\n",5);
  printk("Character = %c\n",'t');
  printk("String = %s\n" , "nice");
  printk("Hex = %x\n" , 12);

	/* init_printf(0, putc); */
  /* printf("Nice\r\n\0"); */

	printk("Initializing I2C...\n");

    i2c_init();


	int ret_val;

	for (int i=0; i<10; i++) {
        char buffer[10];
        ret_val=i2c_recv(21, buffer, 9);
        buffer[9] = 0;

        if (ret_val==0)
	{

       
        printk("Received: %s\n", buffer);


	}
	else 
	{

		printk("mision failed 1, we'll get them next time error: %d \n",ret_val);
	}
       

        delay(500);
    }


	for (unsigned char d=0; d<20; d++) {
        i2c_send(21, &d, 1);

        delay(500);

      if (ret_val==0)
	{

        printk("Sent: %d\n", d);


	}
	else 
	{

		printk("mision failed 2, we'll get them next time error: %d \n",ret_val);
	}
       
    }

     char *msg = "Hello Slave Device";
    i2c_send(21, msg, 18);


    printk("DONE!\n");



	while (1) {
		uart_send(uart_recv());
	}
}

