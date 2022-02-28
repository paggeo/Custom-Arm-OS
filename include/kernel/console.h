#ifndef CONSOLE_H
#define CONSOLE_H
#include <stdint.h>


#define DEVICE_LENGTH 5

#define PROMPT_LENGTH 11

typedef enum{
  cmd_help
} command;

char *console_init(char *device);

int console_get_cmd(char *input);

void console(char *device);

void console_help();



#endif



