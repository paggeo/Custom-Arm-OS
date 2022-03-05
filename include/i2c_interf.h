#ifndef	BSC_I2C
#define	BSC_I2C


void i2c_init();
int i2c_recv(unsigned char address, unsigned char *buffer, uint32_t size);
int i2c_send(unsigned char address, unsigned char *buffer, uint32_t size);


#endif  /*BSC_I2C */