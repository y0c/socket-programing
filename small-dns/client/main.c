#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include "../common/common.h"


typedef struct sock_data {
    int status;
    int content_length;
    char body[200];
} sock_data;


void print_host_ent(struct hostent *myent) {

    printf("Official name : %s\n", myent->h_name);
    printf("Host Type : %s\n", myent->h_addrtype==AF_INET ? "ipv4" : "ipv6");
    printf("Host Length : %d\n", myent->h_length);

    printf("Host Aliases\n");
    while(*myent->h_aliases != NULL ){
        printf("%s\n", *myent->h_aliases);
        myent->h_aliases++;
    }

    printf("Host Addr List\n");
    while(*myent->h_addr_list != NULL ){
        printf("%s\n", *myent->h_addr_list);
        myent->h_addr_list++;
    }
}

char *strsep(char **stringp, const char *delim)
{

    char *ptr = *stringp;

    if(ptr == NULL) {
        return NULL;
    }

    while(**stringp) {
        if(strchr(delim, **stringp) != NULL) {
            **stringp = 0x00;
            (*stringp)++;
            return ptr;
        }
        (*stringp)++;
    }

    *stringp = NULL;
    return ptr;
}

char** str_split(char* str, const char* delim)
{
    char** result;
    char* tmp;
    int cnt = 1;
    int idx = 0;
    char* token;
    tmp = (char*) malloc(strlen(str));
    strcpy(tmp,str);

    while ((token = strsep(&str, delim)) != NULL) {
        cnt++;
    }

    result = (char**)malloc(sizeof(char*) * cnt);


    while ((token = strsep(&tmp, delim)) != NULL) {
        result[idx] = (char*)malloc(sizeof(char*)*strlen(token));
        strcpy(result[idx++],token);
    }

    return result;
}

struct hostent* deserialize(char* str) {
    struct hostent* result = (struct hostent*) malloc(sizeof(struct hostent));
    char** data = str_split(str,"|");

    result->h_name = data[0];
    result->h_addrtype = atoi(data[1]);
    result->h_length = atoi(data[2]);
    result->h_aliases = str_split(data[3],",");
    result->h_addr_list = str_split(data[4],",");

    return result;
}

/**
 * Command line arguments
 * -------------------------------
 *  argv[1]: Target Server ip
 *  argv[2]: query for dns or ip
 *  ------------------------------
 */
int main(int argc, char* argv[]) {

    int sockfd;
    sock_data sdata;
    socklen_t adr_sz;
    struct hostent *hostent;
    struct sockaddr_in serv_adr, from_adr;

    if( argc != 3 ){
        printf("Check Command line arguments");
        exit(1);
    }

    if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == -1 ) {
        printf("socket error!");
        exit(1);
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(3333);

    strcpy(sdata.body, argv[2]);
    sendto(sockfd, (void*) &sdata, sizeof(sdata), 0, (struct sockaddr*) &serv_adr, sizeof(serv_adr));

    adr_sz = sizeof(from_adr);
    memset(&sdata, 0, sizeof(sdata));
    recvfrom(sockfd, (void*)&sdata, sizeof(sdata), 0, (struct sockaddr*)&from_adr, &adr_sz);

    hostent = deserialize(sdata.body);
    print_host_ent(hostent);

    close(sockfd);
    return 0;
}
