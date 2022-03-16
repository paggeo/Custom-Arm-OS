#ifndef CONSOLE_H
#define CONSOLE_H
#include <stdint.h>


#define DEVICE_LENGTH 5

#define PROMPT_LENGTH 11

#define MAX_INPUT_LENGTH 80


typedef enum{
  cmd_help,
  cmd_schedule,
  cmd_cat_1,
  cmd_cat_2
} command;

char *console_init(char *device);
int console_get_cmd(char *input);
void console(char *device);
void console_help();
void console_schedule();
void console_cat_1();
void console_cat_2();



#endif



