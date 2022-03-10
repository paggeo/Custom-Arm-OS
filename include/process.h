#ifndef	_PROCESS_H
#define	_PROCESS_H

void low_priority_process(char *array);
void middle_priority_process(char *array);
void high_priority_process(char *array);

void user_process();
void kernel_process();

void cat(char *array);
void user_process_cat();
void kernel_process_cat();

void create_processes(int proc_num);
void kill_processes();

#endif
