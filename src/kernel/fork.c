#include "mm.h"
#include "sched.h"
#include "entry.h"
#include "clib/printk.h"
#include "utils.h"

int copy_process(unsigned long fn, unsigned long arg)
{
	preempt_disable();
	struct task_struct *p;

	p = (struct task_struct *) get_free_page();
	if (!p)
		return 1;
	p->priority =5; 
	/* p->priority = current->priority; */
	p->state = TASK_RUNNING;
	p->counter = p->priority;
	p->preempt_count = 0; //disable preemtion until schedule_tail

	p->cpu_context.x19 = fn;
	p->cpu_context.x20 = arg;
	p->cpu_context.pc = (unsigned long)ret_from_fork;
	p->cpu_context.sp = (unsigned long)p + THREAD_SIZE;
	int pid = nr_tasks++;
	task[pid] = p;	
	/* printk("Before preempt enable = %d\r\n",p->preempt_count); */
	preempt_enable();
	/* printk("After preempt enable = %d\r\n",p->preempt_count); */
  /* delay(1000); */
	return 0;
}
