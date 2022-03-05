#ifndef	_SYS_H
#define	_SYS_H

#define __NR_syscalls	    4

#define SYS_WRITE_NUMBER    0 		// syscal numbers 
#define SYS_MALLOC_NUMBER   1 	
#define SYS_CLONE_NUMBER    2 	
#define SYS_EXIT_NUMBER     3 	
#define SYS_CAT_NUMBER      4	

#ifndef __ASSEMBLER__

void sys_write(char * buf);
int sys_fork();

void call_sys_write(char * buf);
int call_sys_clone(unsigned long fn, unsigned long arg, unsigned long stack , unsigned int pri);
unsigned long call_sys_malloc();
void call_sys_exit();

void sys_cat(unsigned int num);
void call_sys_cat(unsigned int num);

#endif
#endif  /*_SYS_H */
