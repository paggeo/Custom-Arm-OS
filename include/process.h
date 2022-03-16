#ifndef	_PROCESS_H
#define	_PROCESS_H

void low_priority_process(char *array);
void middle_priority_process(char *array);
void high_priority_process(char *array);

void user_process();
void kernel_process();

void cat_1(char *array);
void cat_2(char *array);
void user_process_cat_1();
void kernel_process_cat_1();
void user_process_cat_2();
void kernel_process_cat_2();

void create_processes(int proc_num);
void kill_processes();

#endif
