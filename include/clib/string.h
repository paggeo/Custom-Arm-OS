/**
 * \defgroup lib lib
 * Basic C Library.
 * @{
 * \defgroup string string
 * Small subset of string.h.
 * @{
 * @file string.h
 * @brief Definition of some string.h functions.
 * https://github.com/thanoskoutr/armOS
 */

#include <stddef.h>

#ifndef STRING_H
#define STRING_H

void *memset(void *s, int c, size_t n);

void *memcpy(void *dest, const void *src, size_t n);

size_t strlen(const char *s);

int strcmp(const char *s1, const char *s2);

char *strcpy(char *dest, const char *src);

char *strcat(char *dest, const char *src);

void strrev(char *s);

#endif
