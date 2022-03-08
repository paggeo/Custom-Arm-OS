#include "utils.h"
#include "clib/printk.h"
#include "sched.h"
#include "peripherals/timer.h"

const unsigned int interval = 20000000;
unsigned int curVal = 0;

void timer_init ( void )
{
	curVal = get32(TIMER_CLO);
	curVal += interval;
	put32(TIMER_C1, curVal);
}

void handle_timer_irq( void ) 
{
	curVal += interval;
	put32(TIMER_C1, curVal);
	put32(TIMER_CS, TIMER_CS_M1);
	printk("timer int recieved\r\n");
	timer_tick();
}