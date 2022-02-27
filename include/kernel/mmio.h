#include <stdint.h>


#ifndef MMIO_H
#define MMIO_H

void mmio_init(int raspi);
/* Memory-Mapped I/O output */
void mmio_write(uint32_t reg, uint32_t data);
/* Memory-Mapped I/O input */
uint32_t mmio_read(uint32_t reg);
/* Loop <count> times, so the compiler won't optimize away */
void delay(int count);

#endif
