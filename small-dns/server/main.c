
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "hashtable.h"

#define PORT 3333
#define DATA_SIZE 60000

typedef struct sock_data {
    int status;
    int content_length;
    char body[DATA_SIZE];
} sock_data;

char* stradd(char* str1, char* str2) {
    char* result;

    if((result = (char*)malloc(strlen(str1) + strlen(str2)+1)) != NULL) {
        result[0] = '\0';
        strcat(result,str1);
        strcat(result,str2);
    } else {
        printf("malloc error");
        result = NULL;
    }

    return result;
}


char* serialize(struct hostent* hp) {
    char* result = "";
    char buf[50];

    sprintf(buf, "%s|%d|%d|", hp->h_name,
            hp->h_addrtype, hp->h_length);
    result = stradd(result, buf);

    while(*hp->h_aliases != NULL ){
        result = stradd(result, inet_ntoa(*(struct in_addr*)*hp->h_aliases));
        if( *(hp->h_aliases+1) != NULL )
            result = stradd(result, ",");
        hp->h_aliases++;
    }

    result = stradd(result, "|");

    while(*hp->h_addr_list != NULL ){
        result = stradd(result, inet_ntoa(*(struct in_addr*)*hp->h_addr_list)) ;
        if( *(hp->h_addr_list+1) != NULL )
            result = stradd(result, ",");
        hp->h_addr_list++;
    }
    result = stradd(result, "|0");

    return result;
}

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
 * Command line arguments
 * -------------------------------
 *  argv[1]: Target Server ip
 *  ------------------------------
 */
int main(int argc, char* argv[]) {
    int sockfd;
    sock_data sdata;

    char*data;
    socklen_t adr_sz;
    struct sockaddr_in addr, cliaddr, hostaddr;
    struct hostent *hostent;
    hashtable_t *hashtable = ht_create(65536);

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1 ){
        printf("socket error");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);


    adr_sz = sizeof(addr);
    if(bind(sockfd, (struct sockaddr*)&addr, adr_sz) == -1 ){
        printf("bind error");
        exit(1);
    }

    while(1) {
        adr_sz = sizeof(cliaddr);
        recvfrom(sockfd, (void*)&sdata, sizeof(sdata), 0, (struct sockaddr*)&cliaddr, &adr_sz);

        printf("Client Info : %s (%d)\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
        printf("%s\n", sdata.body);


        if((data=ht_get(hashtable,sdata.body)) == NULL) {

            if(is_valid_ip_address(sdata.body)) {
                memset(&hostaddr, 0, sizeof(hostaddr));

                hostaddr.sin_addr.s_addr = inet_addr(sdata.body);
                hostent = gethostbyaddr((char*)&hostaddr.sin_addr, 4, AF_INET);

                if(hostent == NULL) {
                    printf("invalid host\n");
                }
            } else {
                hostent = gethostbyname(sdata.body);

                if(hostent == NULL){
                    printf("invalid DNS\n");
                }
            }

            data = serialize(hostent);
            ht_set(hashtable, sdata.body, data);
            printf("set\n");
        } else {
            printf("test\n");
        }


        strcpy(sdata.body, data);
        sdata.body[strlen(data) + 1] = '\0';
        sdata.content_length = strlen(data);

        sendto(sockfd, (void*)&sdata, sizeof(sdata),0,(struct sockaddr*)&cliaddr, adr_sz);

    }
}
