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

//Client / Server 공통적으로 사용할 포트
#define PORT 3333
#define DATA_SIZE 1000
#define HASHTABLE_MAX 65000

//Status Code 통신시 상태를 표현할 코드
#define INVALID_DNS 500
#define INVALID_IP 501
#define SUCCESS 200

//Log Level 로그레벨을 상수로 지정
#define WARN "WARN"
#define ERROR "ERROR"
#define INFO "INFO"

// 호스트 Data를 담을 구조체
typedef struct host_data {
    char* h_name;
    int h_addrtype;
    int h_length;
    char** h_aliases;
    char** h_addr_list;
    int hit;
} host_data;


// 소켓으로 주고받을데이터 구조체
typedef struct sock_data {
    int status;
    int content_length;
    char body[DATA_SIZE];
} sock_data;

//log write 기능
void log_write(FILE *f,char* level, char* message);
//ip format checking
int is_valid_ip_address(char *ip_address);
//inet_ntoa 를 통한 주소변환
char** convert_addr(char** addr_list);
//double pointer 의 row숫자 리턴
int get_row_number(char** str_list);
//호스트Data를 문자열로 직렬화
char* serialize(host_data* hd);
//직렬화된 문자열을 역직렬화
struct host_data* deserialize(char* str);

#endif
