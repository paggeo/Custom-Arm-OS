#include "utils.h"
#include "clib/printk.h"
#include "timer.h"
#include "entry.h"
#include "peripherals/irq.h"

const char *entry_error_messages[] = {
	"SYNC_INVALID_EL1t",
	"IRQ_INVALID_EL1t",		
	"FIQ_INVALID_EL1t",		
	"ERROR_INVALID_EL1T",		

	"SYNC_INVALID_EL1h",		
	"IRQ_INVALID_EL1h",		
	"FIQ_INVALID_EL1h",		
	"ERROR_INVALID_EL1h",		

	"SYNC_INVALID_EL0_64",		
	"IRQ_INVALID_EL0_64",		
	"FIQ_INVALID_EL0_64",		
	"ERROR_INVALID_EL0_64",	

	"SYNC_INVALID_EL0_32",		
	"IRQ_INVALID_EL0_32",		
	"FIQ_INVALID_EL0_32",		
	"ERROR_INVALID_EL0_32",

	"SYNC_ERROR",
	"SYSCALL_ERROR"
};

void enable_interrupt_controller()
{
//#if (MODEL_3 == MODEL)
	//put32(ENABLE_IRQS_1, SYSTEM_TIMER_IRQ_1);
//#elif (MODEL_4 == MODEL)
	put32(IRQ0_SET_EN_1, SYSTEM_TIMER_IRQ_1);
//#endif
}

void show_invalid_entry_message(int type, unsigned long esr, unsigned long address)
{
	printk("%s, ESR: %x, address: %x\r\n", entry_error_messages[type], esr, address);
}

void handle_irq(void)
{
//#if (MODEL_3 == MODEL)
	//unsigned int irq = get32(IRQ_PENDING_1);
//#elif (MODEL_4 == MODEL)
	unsigned int irq = get32(IRQ0_PENDING_1);
//#endif
	switch (irq) {
		case (SYSTEM_TIMER_IRQ_1):
			handle_timer_irq();
			break;
		default:
			printk("Inknown pending irq: %x\r\n", irq);
	}
}
