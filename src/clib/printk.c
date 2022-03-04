/**
 * \ingroup printk
 * @file printk.c
 * @brief Implementation of printk
 * @details Prints a kernel message to the serial console.
 */

#include <stdarg.h>

#include <clib/printk.h>
#include <mini_uart.h>

#include <clib/string.h>
#include <clib/stdlib.h>

int printk(const char *fmt, ...)
{
	va_list ap;

	/* Determine required size */
	va_start(ap, fmt);

	/* Iterate over format string */
	while (*fmt != '\0') {
		/* If a conversion specification is found */
		if (*fmt == '%') {
			/* Find the conversion specifier */
			switch (*(++fmt)) {
			case '%':
				uart_send('%');
				break;
			case 'x':
				/*
				 * Pull of the argument and
				 * Convert int to char* (string)
				 * Print string
				 */
				uart_send_string(itoa(va_arg(ap, unsigned int)));
				break;
			case 'd':
				uart_send_string(itoa(va_arg(ap, int)));
				break;
			case 'c':
				uart_send(va_arg(ap, int));
				break;
			case 's':
				uart_send_string(va_arg(ap, const char *));
				break;
			default:
				break;
			}
		}
		/* If new line, add carriage return */
		else if (*fmt == '\n') {
			uart_send('\r');
			uart_send('\n');
		}
		/* Else print the other characters */
		else {
			uart_send(*fmt);
		}
		fmt++;
	}

	/* clean memory reserved for ap */
	va_end(ap);

	return 0;
}
