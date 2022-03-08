#include "mm.h"
#include "sched.h"
#include "entry.h"
#include "clib/printk.h"
int copy_process(unsigned long fn, unsigned long arg)
{
	preempt_disable();
	struct task_struct *p;
	printk("i am in copy 1\r\n");
	p = (struct task_struct *) get_free_page();
	if (!p)
		return 1;
	p->priority = current->priority;
	p->state = TASK_RUNNING;
	p->counter = p->priority;
	p->preempt_count = 1; //disable preemtion until schedule_tail
	printk("i am in copy 2\r\n");
	p->cpu_context.x19 = fn;
	p->cpu_context.x20 = arg;
	p->cpu_context.pc = (unsigned long)ret_from_fork;
	p->cpu_context.sp = (unsigned long)p + THREAD_SIZE;
	printk("i am in copy 3\r\n");
	int pid = nr_tasks++;
	task[pid] = p;	
	preempt_enable();
	return 0;
}