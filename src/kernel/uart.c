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
    UART1_BASE = (GPIO_BASE + 0x10000), // for raspi4 0xFE210000, raspi2 & 3 0x3F210000, and 0x20210000 for raspi1
 
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

void uart_init(int raspi)
{
	mmio_init(raspi);
 
	// selecting PINs 14,15 alternate mode as TXD1 and RXD1 respectivelly
	unsigned int selector;

	selector = mmio_read(GPFSEL1);
	selector &= ~(7<<12);                   // clean gpio14
	selector |= 2<<12;                      // set alt5 for gpio14
	selector &= ~(7<<15);                   // clean gpio15
	selector |= 2<<15;                      // set alt5 for gpio15
	mmio_write(GPFSEL1,selector);
 
	// Disable pull up/down for all GPIO pins & delay for 150 cycles.
	mmio_write(GPPUD, 0x00000000);
	delay(150);
 
	// Disable pull up/down for pin 14,15 & delay for 150 cycles.
	mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
	delay(150);
 
	// Write 0 to GPPUDCLK0 to make it take effect.
	mmio_write(GPPUDCLK0, 0x00000000);
 
	mmio_write(AUX_ENABLES,1);                   //Enable mini uart (this also enables access to its registers)
	mmio_write(AUX_MU_CNTL_REG,0);               //Disable auto flow control and disable receiver and transmitter (for now)
	mmio_write(AUX_MU_IER_REG,0);                //Disable receive and transmit interrupts
	mmio_write(AUX_MU_LCR_REG,3);                //Enable 8 bit mode
	mmio_write(AUX_MU_MCR_REG,0);                //Set RTS line to be always high
	mmio_write(AUX_MU_BAUD_REG,270);             //Set baud rate to 115200
	mmio_write(AUX_MU_CNTL_REG,3);               //Finally, enable transmitter and receiver
 

}
 
void uart_putc(unsigned char c)
{
	// Wait for UART to become ready to transmit.
	while ( mmio_read(UART0_FR) & (1 << 5) ) { }
	mmio_write(UART0_DR, c);
}
 
unsigned char uart_getc()
{
    // Wait for UART to have received something.
    while ( mmio_read(UART0_FR) & (1 << 4) ) { }
    return mmio_read(UART0_DR);
}
 
void uart_puts(const char* str)
{
	for (size_t i = 0; str[i] != '\0'; i ++)
		uart_putc((unsigned char)str[i]);
}
