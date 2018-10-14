#ifndef COMMON_H
#define COMMON_H
#include "str.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 3333
#define DATA_SIZE 60000

//Status Code
#define INVALID_DNS 500
#define INVALID_IP 501
#define SUCCESS 200

//Log Level
#define WARN "WARN"
#define ERROR "ERROR"
#define INFO "INFO"

typedef struct host_data {
    char* h_name;
    int h_addrtype;
    int h_length;
    char** h_aliases;
    char** h_addr_list;
    int hit;
} host_data;


typedef struct sock_data {
    int status;
    int content_length;
    char body[DATA_SIZE];
} sock_data;

void log_write(FILE *f,char* level, char* message);
int is_valid_ip_address(char *ip_address);
char** convert_addr(char** addr_list);
int get_row_number(char** str_list);
char* serialize(host_data* hd);
struct host_data* deserialize(char* str);

#endif
