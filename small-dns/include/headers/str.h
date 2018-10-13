#ifndef STRING_H
#define STRING_H
#include <string.h>
#include <stdlib.h>
void str_rmchr(char *s, char chr);
char* str_join(char** str, char* delim);
char *str_sep(char **stringp, const char *delim);
char** str_split(const char* str, const char* delim);
char* str_add(char* str1, char* str2);

#endif
