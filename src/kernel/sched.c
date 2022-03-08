#include "sched.h"
#include "irq.h"
#include "clib/printk.h"

static struct task_struct init_task = INIT_TASK;
struct task_struct *current = &(init_task);
struct task_struct * task[NR_TASKS] = {&(init_task), };
int nr_tasks = 1;

void preempt_disable(void)
{
	current->preempt_count=1;
}

void preempt_enable(void)
{
	current->preempt_count=0;
}


void _schedule(void)
{   printk("got here 3\r\n");
	preempt_disable();
    printk("got here 4\r\n");
	int next,c;
	struct task_struct * p;
	while (1) {
		c = -1;
		next = 0;
		for (int i = 0; i < NR_TASKS; i++){
			p = task[i];
			if (p && p->state == TASK_RUNNING && p->counter > c) {
				c = p->counter;
				next = i;
			}
		}
        printk("got here 5\r\n");
		if (c) {
			break;
		}
        printk("got here 6\r\n");
		for (int i = 0; i < NR_TASKS; i++) {
			p = task[i];
			if (p) {
				p->counter = (p->counter >> 1) + p->priority;
			}
		}
	}
    printk("got here 7\r\n");
	switch_to(task[next]);
    printk("got here 8\r\n");
	preempt_enable();
}

void schedule(void)
{
	current->counter = 0;
	_schedule();
}

void switch_to(struct task_struct * next) 
{
	if (current == next) 
		return;
    printk("got here A\r\n");    
	struct task_struct * prev = current;
	current = next;
    printk("got here B\r\n"); 
    //if (current->first_time){ret_from_fork();}
    printk("i am before cpu switch\r\n");
	cpu_switch_to(prev, next);
}

void schedule_tail(void) {
    printk("i am in schedule tail\r\n");
	preempt_enable();
    printk("i am out of schedule tail\r\n");
}


void timer_tick()
{   printk("got here\r\n");
    /*if (current->counter>2147483640){
	current->counter=0;}
    if (current->counter>0){
	--current->counter;}*/
    printk("Before counter :%d\r\n",current->counter);
    printk("Before counter :%d\r\n",current->preempt_count);
	if (current->counter>0 || current->preempt_count >0) {
		return;
	}
    printk("got here 2 \r\n");
	current->counter=0;
	enable_irq();
	_schedule();
	disable_irq();
}