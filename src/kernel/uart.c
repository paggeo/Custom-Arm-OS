#include <stddef.h>
#include <stdint.h>

#include <kernel/uart.h>
#include <kernel/mmio.h>

enum
{
    // The offsets for reach register.
    GPIO_BASE = 0x200000,
 
    // Controls actuation of pull up/down to ALL GPIO pins.
    GPPUD = (GPIO_BASE + 0x94),
 
    // Controls actuation of pull up/down for specific GPIO pin.
    GPPUDCLK0 = (GPIO_BASE + 0x98),
    // Controls alternative functions for pins 10-19
    GPFSEL1 = (GPIO_BASE + 0x04),        
    // The base address for UART.
    UART1_BASE = (GPIO_BASE + 0x15000), // for raspi4 0xFE215000, raspi2 & 3 0x3F215000, and 0x20215000 for raspi1
 
    // The offsets for reach register for the UART.
	
	
	
	AUX_ENABLES = (UART1_BASE+0x04),
	AUX_MU_IO_REG = (UART1_BASE+0x40),
	AUX_MU_IER_REG = (UART1_BASE+0x44),
	AUX_MU_IIR_REG = (UART1_BASE+0x48),
	AUX_MU_LCR_REG = (UART1_BASE+0x4C),
	AUX_MU_MCR_REG = (UART1_BASE+0x50),
	AUX_MU_LSR_REG = (UART1_BASE+0x54),
	AUX_MU_MSR_REG = (UART1_BASE+0x58),
	AUX_MU_SCRATCH = (UART1_BASE+0x5C),
	AUX_MU_CNTL_REG = (UART1_BASE+0x60),
	AUX_MU_STAT_REG = (UART1_BASE+0x64),
	AUX_MU_BAUD_REG = (UART1_BASE+0x68)
 
};
void uart_putc (unsigned char c )
{
	while(1) {
		if(mmio_read(AUX_MU_LSR_REG)&0x20) 
			break;
	}
	mmio_write(AUX_MU_IO_REG,c);
}

unsigned char uart_getc (  )
{
	while(1) {
		if(mmio_read(AUX_MU_LSR_REG)&0x01) 
			break;
	}
	return(mmio_read(AUX_MU_IO_REG)&0xFF);
}

void uart_puts(const char* str)
{
	for (int i = 0; str[i] != '\0'; i ++) {
		uart_putc((char)str[i]);
	}
}

void uart_init ( int raspi )
{

	mmio_init(raspi);

	unsigned int selector;

	selector = mmio_read(GPFSEL1);
	selector &= ~(7<<12);                   // clean gpio14
	selector |= 2<<12;                      // set alt5 for gpio14
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 2<<15;                      // set alt5 for gpio15
	mmio_write(GPFSEL1,selector);

	mmio_write(GPPUD,0);
	delay(150);
	mmio_write(GPPUDCLK0,(1<<14)|(1<<15));
	delay(150);
	mmio_write(GPPUDCLK0,0);

	mmio_write(AUX_ENABLES,1);                   //Enable mini uart (this also enables access to its registers)
	mmio_write(AUX_MU_CNTL_REG,0);               //Disable auto flow control and disable receiver and transmitter (for now)
	mmio_write(AUX_MU_IER_REG,0);                //Disable receive and transmit interrupts
	mmio_write(AUX_MU_LCR_REG,3);                //Enable 8 bit mode
	mmio_write(AUX_MU_MCR_REG,0);                //Set RTS line to be always high
	mmio_write(AUX_MU_BAUD_REG,270);             //Set baud rate to 115200

	mmio_write(AUX_MU_CNTL_REG,3);               //Finally, enable transmitter and receiver
}