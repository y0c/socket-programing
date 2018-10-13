#include "common.h"

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
        10,
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

    hostdata->h_name = data[0];
    hostdata->h_addrtype = atoi(data[1]);
    hostdata->h_length = atoi(data[2]);
    hostdata->h_aliases = str_split(data[3],",");
    hostdata->h_addr_list = str_split(data[4],",");
    hostdata->hit = atoi(data[5]);

    return hostdata;
}
