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
  adr x0, _bss_begin
  adr x1, _bss_end
  sub x1 , x1 , x0 // x1 = end - begin = length
  bl memzero 
  mov sp , 0x80000
  bl kernel_main

  // failure detection, shouldn't reach here
  b proc_hang 
