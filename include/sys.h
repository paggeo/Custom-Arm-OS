#ifndef	_SYS_H
#define	_SYS_H

#define __NR_syscalls	    7

#define SYS_WRITE_NUMBER        0 		// syscal numbers 
#define SYS_MALLOC_NUMBER       1 	
#define SYS_CLONE_NUMBER        2 	
#define SYS_EXIT_NUMBER         3 	
#define SYS_CAT_NUMBER          4 	
#define SYS_PRIORITY_NUMBER     5 	
#define SYS_GET_PRIORITY_NUMBER     6 	

#ifndef __ASSEMBLER__

void sys_write(char * buf);
int sys_fork();

void call_sys_write(char * buf);
int call_sys_clone(unsigned long fn, unsigned long arg, unsigned long stack);
unsigned long call_sys_malloc();
void call_sys_exit();

void sys_cat(unsigned int num);
void call_sys_cat(unsigned int num);

void call_sys_change_prior(long priority);
void sys_change_prior(long priority);

long call_sys_get_prior();
long sys_get_prior();

#endif
#endif  /*_SYS_H */
