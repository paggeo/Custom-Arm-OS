#ifndef	_PROCESS_H
#define	_PROCESS_H
void low_priority_process(char *array);
void middle_priority_process(char *array);
void high_priority_process(char *array);
void user_process();
void kernel_process();
void process1(char *array);
void create_processes(int proc_num);
void kill_processes();
#endif
