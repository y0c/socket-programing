#include "common.h"

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

int get_row_number(char** str_list){
    char** temp = str_list;
    int i = 0;
    while(*temp != NULL ){
       temp++;
       i++;
    }

    return i;
}

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
        "%s|%d|%d|%s|%s|%d",
        hd->h_name,
        hd->h_addrtype,
        hd->h_length,
        str_join(hd->h_aliases,","),
        str_join(hd->h_addr_list,","),
        hd->hit
    );

    return result;
}

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
