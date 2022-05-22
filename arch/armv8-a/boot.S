#include "arm/sysregs.h"

.global _start


_start:
	mrs x0, mpidr_el1
	and x0, x0, #0xFF	// Check processor id
	cbz x0, master		// Hang for all non-primary CPU
	b proc_hang
proc_hang:
	b proc_hang

master:
	ldr x0, =SCTLR_VALUE_MMU_DISABLED
	msr sctlr_el1, x0


	ldr x0, =HCR_VALUE
	msr hcr_el2, x0

	ldr x0, =SCR_VALUE
	msr scr_el3, x0

	ldr x0, =SPSR_VALUE
	msr spsr_el3, x0

	adr x0, el1_entry
	msr elr_el3, x0

	eret

el1_entry:
	mov sp, #0x80000		// Setup the stack (64 bit).

	ldr x5, =__bss_start		// Clear out BSS.
	ldr w6, =__bss_size
clear_bss:
	cbz w6, kernel_entry
	str xzr, [x5], #8
	sub w6, w6, #1
	cbnz w6, clear_bss

kernel_entry:
	bl kernel_main			// Call kernel_main (C Code).

	b proc_hang			// For failsafe, halt this core too.
