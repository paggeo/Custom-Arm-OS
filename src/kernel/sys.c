#include "fork.h"
#include "clib/printk.h"
#include "utils.h"
#include "sched.h"
#include "mm.h"
#include "irq.h"

void sys_write(char * buf){
	printk("%s",buf);
}

int sys_clone(unsigned long stack){
	return copy_process(0, 0, 0, stack);
}

unsigned long sys_malloc(){
	unsigned long addr = get_free_page();
	if (!addr) {
		return -1;
	}
	return addr;
}

void sys_exit(){
	exit_process();
}
void sys_cat(unsigned int num){
	if(num ==1 ){
    printk("             *     ,MMM8&&&.            *\n"); 
    printk("                  MMMM88&&&&&    .\n");  
    printk("                 MMMM88&&&&&&&\n");  
    printk("     *           MMM88&&&&&&&&\n");  
    printk("                 MMM88&&&&&&&&\n");  
    printk("                 'MMM88&&&&&&'\n");  
    printk("                   'MMM8&&&'      *    _\n");  
    printk("          ||___||                      \\n"); 
    printk("         =) ^Y^ (=   ||_||              ||    '\n");  
    printk("          |  ^  |    )a a '._.-""""-.  //\n");  
    printk("           )=*=(    =|T_= /    ~  ~  |//\n");  
    printk("          /     |     ``|   ~   / ~  /\n");  
    printk("          |     |         |~   | |  ~/\n");  
    printk("         /| | | ||         |  ~/- | ~\\n"); 
    printk("         || | |_|/|        || |  // /`\n"); 
    printk("  jgs_/|_//_// __//|_/|_/|_((_||((_//|_/|_/|_\n");  
    printk(" |  |  |  | |_) |  |  |  |  |  |  |  |  |  |\n");  
    printk(" |  |  |  | |_) |  |  |  |  |  |  |  |  |  |\n");  
    printk(" |  |  |  | |_) |  |  |  |  |  |  |  |  |  |\n");     
    printk(" |  |  |  | |_) |  |  |  |  |  |  |  |  |  |\n");  
    printk(" |  |  |  | |_) |  |  |  |  |  |  |  |  |  |\n");  
    }
    else if (num ==2) {
        printk("                                 _\n"); 
        printk("                                | \n"); 
        printk("                                | |\n"); 
        printk("                                | |\n"); 
        printk("           ||                  | |\n"); 
        printk("          /, ~|                / /\n"); 
        printk("         X     `-.....-------./ /\n"); 
        printk("          ~-. ~  ~              |\n"); 
        printk("             |             /    |\n"); 
        printk("              |  /_     ___|   /\n"); 
        printk("              | /| ~~~~~   |  |\n"); 
        printk("              | | |        || |\n"); 
        printk("              | || |       || )\n"); 
        printk("             (_/ (_/      ((_/\n"); 

    }
    else {printk("Wrong number of cat, try 1 or 2");}
}

void sys_change_prior(long priority){
    current->priority = priority;
}
void * const sys_call_table[] = {sys_write, sys_malloc, sys_clone, sys_exit, sys_cat, sys_change_prior};
