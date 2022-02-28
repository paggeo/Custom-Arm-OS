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
	

	adr x5, bss_begin		// Clear out BSS.
	adr x6, bss_end
	sub x6,x6,x5

clear_bss:
	// cbz x6, kernel_entry 

	str xzr, [x5], #8
	subs x6, x6, #1
	b.gt clear_bss


mov sp, #0x400000	// Setup the stack (64 bit).
kernel_entry:
	bl kernel_main			// Call kernel_main (C Code).
					// Should not return from here.

	b proc_hang			// For failsafe, halt this core too.
