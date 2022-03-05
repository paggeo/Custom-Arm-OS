#include "peripherals/i2c.h"
#include "peripherals/gpio.h"
#include "utils.h"
#include <stdint.h>
#include <clib/printf.h>
#include "mini_uart.h"
#include <clib/printk.h>

void i2c_init()
{
	unsigned int selector;

	selector = get32(GPFSEL0);
	selector &= ~(7<<6);                    // clean gpio2
	selector |= 4<<6;                       // set alt0 for gpio2
	selector &= ~(7<<9);                    // clean gpio3
	selector |= 4<<9;                      // set alt0 for gpio3
	put32(GPFSEL0,selector);

	put32(GPPUD,0);
	delay(150);
	put32(GPPUDCLK0,(1<<2)|(1<<3));
	delay(150);
	put32(GPPUDCLK0,0);

    put32(Clk_Div_reg,core_speed/I2C_SPEED);

}

int i2c_recv(unsigned char address, unsigned char *buffer, uint32_t size)
{
//----- return values ----- //
    //Success: 0
    //Error: 1
    //Timeout: 2
    //Data_Loss: 3
   
//using 7-bit addressing mode
put32(Slave_Address_reg,address); //address is actually 7 bits, but we are using standard 8 bit type
put32(Control_reg,C_CLEAR);
put32(Status_reg, S_CLKT | S_ERR | S_DONE);

put32(Data_Lenght_reg, size);

// enable BSC controller, start transfer and read mode ON.
put32(Control_reg,C_I2CEN | C_ST | C_READ);

uint32_t bytes_read=0;





while(!( get32(Status_reg) & S_DONE ) ) {
        while( get32(Status_reg) & S_RXD ) {
            *buffer++ = get32(FIFO_reg) & 0xFF;
            bytes_read++;
        }
    }

// *important* done flag might be set before FIFO has been read completely
    while(bytes_read < size && ( get32(Status_reg) & S_RXD) ) {
        *buffer++ = get32(FIFO_reg) & 0xFF;
        bytes_read++;
    }

    uint32_t status = get32(Status_reg) ;

    put32(Status_reg,S_DONE);

    if (status & S_ERR) {
        return 1;
    } else if (status & S_CLKT) {
        return 2;
    } else if (bytes_read < size) {
        return 3;
    }

    return 0;

}



int i2c_send(unsigned char address, unsigned char *buffer, uint32_t size)
{

//----- return values ----- //
    //Success: 0
    //Error: 1
    //Timeout: 2
    //Data_Loss: 3
   

uint32_t bytes_written=0;

    put32(Slave_Address_reg,address);
    put32(Control_reg,C_CLEAR);
    put32(Status_reg, S_CLKT | S_ERR | S_DONE);     
    put32(Data_Lenght_reg, size);


    put32(Control_reg,C_I2CEN | C_ST); //not reading == writing

while(!( get32(Status_reg) & S_DONE ) ) {
        while( bytes_written < size && ( get32(Status_reg) & S_TXD) ) {
        put32(FIFO_reg,*buffer++); 
        bytes_written++;

       // printk("yeah baby boy\r\n");
    }

   // THis point IIS indeed reached

    }
/*
// *important* done flag might be set before FIFO has been "sent" completely 
    while(bytes_written < size && ( get32(Status_reg) & S_TXD) ) {
        put32(FIFO_reg,*buffer++); 
        bytes_written++;
    }
printk("yeah baby\r\n");

   */
  //  printk("yeah baby girl\r\n");
   uint32_t status = get32(Status_reg) ;

    put32(Status_reg,S_DONE);

    if (status & S_ERR) {
        return 1;
    } else if (status & S_CLKT) {
        return 2;
    } else if (bytes_written < size) {
        return 3;
    }

    return 0;
}


