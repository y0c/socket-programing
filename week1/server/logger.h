#ifndef LOGGER_H
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define ERROR "ERROR"
#define WARN "WARN" 
#define INFO "INFO" 

#endif

void log_init();
void log_destory();
void log_write(char* level, char* message);