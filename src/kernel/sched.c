#include "sched.h"
#include "irq.h"
#include "clib/printk.h"
#include "fork.h"
#include "utils.h"
#include "mm.h"

static struct task_struct init_task = INIT_TASK;
struct task_struct *current = &(init_task);
struct task_struct * task[NR_TASKS] = {&(init_task), };
int nr_tasks = 1;


void preempt_disable(void)
{
	current->preempt_count=SCHED_PRIORITY;
}

void preempt_enable(void)
{
	current->preempt_count=0;
}


void _schedule(void)
{
	preempt_disable();
	int next,c,pri;
	struct task_struct * p;
	while (1) {
		c = -1;
    pri = -1;
		next = 0;
		for (int i = 0; i < NR_TASKS; i++){
			p = task[i];
      if(p && p->state == TASK_RUNNING){
        if (p->counter > c){
          c = p->counter;
          pri = p->priority;
          next = i;
        }
      }
		}
		if (c) {
			break;
		}
		for (int i = 0; i < NR_TASKS; i++) {
			p = task[i];
			if (p && p->state == TASK_RUNNING) {
				if (p->counter >10 && p->priority == LOW_PRIORITY) p->priority = MIDDLE_PRIORITY;
				if (p->counter >10 && p->priority == MIDDLE_PRIORITY) p->priority = HIGH_PRIORITY;
        p->counter = (p->counter >> 1) + 10*p->priority;
        
			}
		}
	}
	switch_to(task[next], next);
	preempt_enable();
}

void schedule(void)
{
	current->counter = 0;
	_schedule();
}


void switch_to(struct task_struct * next, int index) 
{
	if (current == next) 
		return;
  printk("\n\t\tContext switch\n");
	struct task_struct * prev = current;
	current = next;
	cpu_switch_to(prev, next);
}

void schedule_tail(void) {
	preempt_enable();
}

void timer_tick()
{
	--current->counter;
	if (current->counter>0 || current->preempt_count == SCHED_PRIORITY || (current->state != TASK_ZOMBIE && current->priority== HIGH_PRIORITY)) {
		return;
	}
	current->counter=0;
	enable_irq();
	_schedule();
	disable_irq();
}

void exit_process(){
	preempt_disable();
	for (int i = 0; i < NR_TASKS; i++){
		if (task[i] == current) {
			task[i]->state = TASK_ZOMBIE;
			break;
		}
	}
	if (current->stack) {
		free_page(current->stack);
	}
	preempt_enable();
	schedule();
}
