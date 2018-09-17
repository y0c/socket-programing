#include "logger.h"

FILE* f = NULL;

void log_init() {
    f = fopen("server.log", "a");

    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
}

void log_destory() {
    fclose(f);
}

void log_write(char* level, char* message) {
    time_t timer;
    char buffer[26];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    printf("%s [%s] %s\n",level, buffer, message);
    fprintf(f, "%s [%s] %s\n",level, buffer, message);
    fflush(f);
}