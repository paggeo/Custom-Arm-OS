#include <stdint.h>

#include <kernel/console.h>
#include <kernel/uart.h>


#include <clib/printf.h>
#include <clib/string.h>


char *console_init(char *device)
{
	static char prompt[PROMPT_LENGTH];

	/* Create prompt */
	strcpy(prompt, "root@");
	strcat(prompt, device);
	strcat(prompt, "#");

	return prompt;
}

int console_get_cmd(char *input)
{
	if (strcmp(input, "help") == 0)
		return cmd_help;
	else
		return -1;
}

void console(char *device)
{
	char *input;
	char *args;
	char *prompt;
	int msec, count, pin_num, proc_num;

	/* Get prompt */
	prompt = console_init(device);

	/* Print console info */
	printf("\n");
	printf("This is a minimal console, type 'help' to see the available commands. (Maximum Input Length: %d)\n", MAX_INPUT_LENGTH);

	/* Main functionality */
	while (1) {
		/* Print prompt */
		printf("%s ", prompt);
		/* Read from serial */
		input = uart_gets();
		printf("\n");
    command cmd = console_get_cmd(input);

		switch (cmd) {
      case cmd_help:
        console_help();
        break;
      default:
        printf("%s: command not found\n", input);
        printf("type 'help' to see the available commands\n");
        break;
		  }
  }
}

void console_help()
{
	printf("Available commands:\n");
	printf("    help:\n");
	printf("        Prints available commands to the console.\n");
}
