#include "mm.h"
#include "sched.h"
#include "entry.h"
#include "clib/printk.h"

int copy_process(unsigned long fn, unsigned long arg)
{
	preempt_disable();
	struct task_struct *p;

	p = (struct task_struct *) get_free_page();
	if (!p)
		return 1;
	p->priority =  current->priority;
	p->state = TASK_RUNNING;
	p->counter = p->priority;
    p->first_time = 1;
	p->preempt_count = 0; //disable preemtion until schedule_tail

	p->cpu_context.x19 = fn;
	p->cpu_context.x20 = arg;
	p->cpu_context.pc = (unsigned long) ret_from_fork;
    printk("i am at the spot\r\n");
    
   
	p->cpu_context.sp = (unsigned long) p + THREAD_SIZE;
	int pid = nr_tasks++;
	task[pid] = p;	
  
    
	preempt_enable();
      ret_from_fork();
     printk("Before counter :%d\r\n",ret_from_fork);
	return 0;
}