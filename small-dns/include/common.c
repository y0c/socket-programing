#include "common.h"

/**
 * Function: is_valid_ip_address
 * IP 형식을 검사
 * --------------------------------------
 *  ip_address: 검사할 ip 주소
 *  return : true or false
 */
int is_valid_ip_address(char *ip_address)
{
    int a[4];
    int i;
    int rc = sscanf(ip_address, "%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]);
    if (rc < 4) return 0;
    for(i = 0; i < 4; i ++ )
        if(a[i] > 255 || a[i] <= 0 ) return 0;

    return 1;
}


/**
 * Function: get_row_number
 * 이중포인터의 row수를 계산
 * --------------------------------------
 *  str_list: char 형 이중포인터
 *  return: 이중포인터 row 수
 */
int get_row_number(char** str_list){
    char** temp = str_list;
    int i = 0;
    while(*temp != NULL ){
       temp++;
       i++;
    }

    return i;
}

/**
 * Function: convert_addr
 * 주소목록을 inet_ntoa로 변환
 * --------------------------------------
 *  addr_list: address list
 *  return: inte_ntoa를 통해 변환된 목록
 */
char** convert_addr(char** addr_list){
    char** temp = addr_list;
    char** result = (char**)calloc(get_row_number(addr_list)+1,sizeof(char*));
    char* caddr;
    char** rtemp = result;

    while(*temp!=NULL){
        caddr = inet_ntoa(*(struct in_addr*)*temp);
        *rtemp = (char*)malloc(strlen(caddr));
        strcpy(*rtemp, caddr);
        temp++;
        rtemp++;
    }

    *rtemp = NULL;

    return result;
}


/**
 * Function: serialize
 * host_data를 직렬화
 * --------------------------------------
 *  host_data*: 직렬화할 host_data
 *  return: 직렬화된 문자열
 */
char* serialize(struct host_data* hd) {
    char* result;
    char* addr_list = str_join(hd->h_addr_list,",");
    char* aliases = str_join(hd->h_aliases,",");

    result = (char*)calloc(
        strlen(hd->h_name) +
        sizeof(hd->h_addrtype) +
        sizeof(hd->h_length) +
        strlen(aliases) +
        strlen(addr_list) +
        100,
        sizeof(char)
    );


    sprintf(
        result,
        "%s|%d|%d|%s|%s|%10d",
        hd->h_name,
        hd->h_addrtype,
        hd->h_length,
        str_join(hd->h_aliases,","),
        str_join(hd->h_addr_list,","),
        hd->hit
    );

    return result;
}


/**
 * Function: deserialize
 * 직렬화된 문자열을 구조체로 변경
 * --------------------------------------
 *  str*: 직렬화된 문자열
 *  return: host_data 구조체
 */
struct host_data* deserialize(char* str) {
    host_data* hostdata = (host_data*) malloc(sizeof(host_data));
    char** data = str_split(str,"|");

    if(str == NULL ) {
        return NULL;
    }

    hostdata->h_name = data[0];
    hostdata->h_addrtype = atoi(data[1]);
    hostdata->h_length = atoi(data[2]);
    hostdata->h_aliases = str_split(data[3],",");
    hostdata->h_addr_list = str_split(data[4],",");
    hostdata->hit = atoi(data[5]);

    return hostdata;
}

/**
 * Function: log_write
 * File에 로그를 작성
 * --------------------------------------
 *  FILE* f: 로그를저장할 파일
 *  char* level: log level을 설정
 *  char* message: log message
 */
void log_write(FILE *f,char* level,  char* message) {

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
