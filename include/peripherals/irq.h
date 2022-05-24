#ifndef	_P_IRQ_H
#define	_P_IRQ_H

#include "peripherals/base.h"

#if (MODEL_3 == MODEL)
	/** For raspi 2,3: PBASE = 0x3F000000 */
    #define IRQ_BASIC_PENDING	(PBASE+0x0000B200)
    #define IRQ_PENDING_1		(PBASE+0x0000B204)
    #define IRQ_PENDING_2		(PBASE+0x0000B208)
    #define FIQ_CONTROL		    (PBASE+0x0000B20C)
    #define ENABLE_IRQS_1		(PBASE+0x0000B210)
    #define ENABLE_IRQS_2		(PBASE+0x0000B214)
    #define ENABLE_BASIC_IRQS	(PBASE+0x0000B218)
    #define DISABLE_IRQS_1		(PBASE+0x0000B21C)
    #define DISABLE_IRQS_2		(PBASE+0x0000B220)
    #define DISABLE_BASIC_IRQS	(PBASE+0x0000B224)
#elif (MODEL_4 == MODEL)
    #define IRQ_BASE  (PBASE + 0xB000),
    #define IRQ0_PENDING_0      (IRQ_BASE + 0x200)
    #define IRQ0_PENDING_1      (IRQ_BASE + 0x204)
    #define IRQ0_PENDING_2      (IRQ_BASE + 0x208)
    #define IRQ0_SET_EN_0       (IRQ_BASE + 0x210)
    #define IRQ0_SET_EN_1       (IRQ_BASE + 0x214)
    #define IRQ0_SET_EN_2       (IRQ_BASE + 0x218)
    #define IRQ0_CLR_EN_0       (IRQ_BASE + 0x220)
    #define IRQ0_CLR_EN_1       (IRQ_BASE + 0x224)
    #define IRQ0_CLR_EN_2       (IRQ_BASE + 0x228)
#endif

#define SYSTEM_TIMER_IRQ_0	(1 << 0)
#define SYSTEM_TIMER_IRQ_1	(1 << 1)
#define SYSTEM_TIMER_IRQ_2	(1 << 2)
#define SYSTEM_TIMER_IRQ_3	(1 << 3)

#endif  /*_P_IRQ_H */
