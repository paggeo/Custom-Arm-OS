#ifndef	BSC_I2C
#define	BSC_I2C


#include "peripherals/base.h"

#define BSC1_BASE (PBASE + 0x00804000)


#define I2C_SPEED 100000 // define i2c speed at 100khz
#define core_speed 250000000 //define core_speed at 250Mhz as set in config file.


#define Control_reg              (BSC1_BASE+0x00)
#define Status_reg               (BSC1_BASE+0x04)
#define Data_Lenght_reg          (BSC1_BASE+0x08)
#define Slave_Address_reg        (BSC1_BASE+0x0C)
#define FIFO_reg                 (BSC1_BASE+0x10)
#define Clk_Div_reg              (BSC1_BASE+0x14)
#define Data_Delay_reg           (BSC1_BASE+0x18)
#define Clk_Stretch_Timeout_reg  (BSC1_BASE+0x1C)


//Control register
#define C_I2CEN			(1 << 15)
#define C_INTR			(1 << 10)
#define C_INTT			(1 << 9)
#define C_INTD			(1 << 8)
#define C_ST			(1 << 7)
#define C_CLEAR			(1 << 5)
#define C_READ			(1 << 0)

// Status register
#define S_CLKT			(1 << 9)
#define S_ERR			(1 << 8)
#define S_RXF			(1 << 7)
#define S_TXE			(1 << 6)
#define S_RXD			(1 << 5)
#define S_TXD			(1 << 4)
#define S_RXR			(1 << 3)
#define S_TXW			(1 << 2)
#define S_DONE			(1 << 1)
#define S_TA			(1 << 0)


#endif  /*BSC_I2C */
