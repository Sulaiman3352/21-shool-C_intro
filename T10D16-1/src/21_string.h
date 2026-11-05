#ifndef DATA_IO_H
#define DATA_IO_H  
#define restrict 
#include "./stddef.h"
#include "./locale.h" 

void s21_strlen();
size_t   strlen(const char *);
int      strcmp(const char *, const char *);
char    *strcpy(char *restrict, const char *restrict);
char    *strcat(char *restrict, const char *restrict);
char    *strchr(const char *, int);
char    *strstr(const char *, const char *);
size_t   strnlen(const char *, size_t);
int      strncmp(const char *, const char *, size_t);

#endif