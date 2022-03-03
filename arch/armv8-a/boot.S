.section ".text.boot"

.global _start 

_start:
    /* Start only one core*/
    mrs x0, mpidr_el1
    and x0, x0 , #0xFF
    cbz x0, master 
    b proc_hang

proc_hang:
  b proc_hang

master: 
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
					// Should not return from here.

	b proc_hang			// For failsafe, halt this core too.