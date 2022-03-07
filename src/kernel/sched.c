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
	/* current->preempt_count++; */
}

void preempt_enable(void)
{
	current->preempt_count=0;
	/* current->preempt_count--; */
}


void _schedule(void)
{
  /* printk("starting schedule\r\n"); */
	preempt_disable();
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
		if (c) {
			break;
		}
		for (int i = 0; i < NR_TASKS; i++) {
			p = task[i];
			if (p) {
				p->counter = (p->counter >> 1) + p->priority;
			}
		}
	}
  /* printk("pre switch task schedule\r\n"); */
	switch_to(task[next]);
  /* printk("after switch task schedule\r\n"); */
	preempt_enable();
}

void schedule(void)
{
  /* printk("real schedule\r\n"); */
	current->counter = 0;
	_schedule();
}

void switch_to(struct task_struct * next) 
{
	if (current == next) 
		return;
	struct task_struct * prev = current;
	current = next;
	cpu_switch_to(prev, next);
}

void schedule_tail(void) {
	preempt_enable();
}


void timer_tick()
{
	/* printk("Before counter :%d\r\n",current->counter); */
	--current->counter;
	/* printk("After counter :%d\r\n",current->counter); */
	/* printk("preempt_count :%d\r\n",current->preempt_count); */
	if (current->counter>0 || current->preempt_count >0) {
		return;
	}
	current->counter=0;
	/* printk("Before int\r\n"); */
	enable_irq();
	/* printk("After int\r\n"); */
	_schedule();
	/* printk("After sched\r\n"); */
	disable_irq();
	/* printk("Dis int\r\n"); */
}
