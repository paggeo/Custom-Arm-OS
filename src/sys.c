#include "fork.h"
#include "printf.h"
#include "utils.h"
#include "sched.h"
#include "mm.h"

void sys_write(char * buf){
	printf(buf);
}

int sys_clone(unsigned long stack){
	return copy_process(0, 0, 0, 1, stack);
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
    printf("             *     ,MMM8&&&.            *\n"); 
    printf("                  MMMM88&&&&&    .\n");  
    printf("                 MMMM88&&&&&&&\n");  
    printf("     *           MMM88&&&&&&&&\n");  
    printf("                 MMM88&&&&&&&&\n");  
    printf("                 'MMM88&&&&&&'\n");  
    printf("                   'MMM8&&&'      *    _\n");  
    printf("          ||___||                      \\n"); 
    printf("         =) ^Y^ (=   ||_||              ||    '\n");  
    printf("          |  ^  |    )a a '._.-""""-.  //\n");  
    printf("           )=*=(    =|T_= /    ~  ~  |//\n");  
    printf("          /     |     ``|   ~   / ~  /\n");  
    printf("          |     |         |~   | |  ~/\n");  
    printf("         /| | | ||         |  ~/- | ~\\n"); 
    printf("         || | |_|/|        || |  // /`\n"); 
    printf("  jgs_/|_//_// __//|_/|_/|_((_||((_//|_/|_/|_\n");  
    printf(" |  |  |  | |_) |  |  |  |  |  |  |  |  |  |\n");  
    printf(" |  |  |  | |_) |  |  |  |  |  |  |  |  |  |\n");  
    printf(" |  |  |  | |_) |  |  |  |  |  |  |  |  |  |\n");     
    printf(" |  |  |  | |_) |  |  |  |  |  |  |  |  |  |\n");  
    printf(" |  |  |  | |_) |  |  |  |  |  |  |  |  |  |\n");  
    }
    else if (num ==2) {
        printf("                                 _\n"); 
        printf("                                | \n"); 
        printf("                                | |\n"); 
        printf("                                | |\n"); 
        printf("           ||                  | |\n"); 
        printf("          /, ~|                / /\n"); 
        printf("         X     `-.....-------./ /\n"); 
        printf("          ~-. ~  ~              |\n"); 
        printf("             |             /    |\n"); 
        printf("              |  /_     ___|   /\n"); 
        printf("              | /| ~~~~~   |  |\n"); 
        printf("              | | |        || |\n"); 
        printf("              | || |       || )\n"); 
        printf("             (_/ (_/      ((_/\n"); 

    }
    else {printf("Wrong number of cat, try 1 or 2");}
}

void * const sys_call_table[] = {sys_write, sys_malloc, sys_clone, sys_exit, sys_cat};
