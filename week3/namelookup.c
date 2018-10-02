#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>

void printHostent(struct hostent *myent) {

    printf("Official name : %s\n", myent->h_name);
    printf("Host Type : %s\n", myent->h_addrtype==AF_INET ? "ipv4" : "ipv6");
    printf("Host Length : %d\n", myent->h_length);

    printf("Host Aliases\n");
    while(*myent->h_aliases != NULL ){
        printf("%s\n", inet_ntoa(*(struct in_addr*)*myent->h_aliases));
        myent->h_aliases++;
    }

    printf("Host Addr List\n");
    while(*myent->h_addr_list != NULL ){
        printf("%s\n", inet_ntoa(*(struct in_addr*)*myent->h_addr_list));
        myent->h_addr_list++;
    }
}

int isValidIpAddress(char *ipAddress)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    return result;
}


int main(int argc, char** argv) {

    struct hostent *hostent;
    struct sockaddr_in addr;

    if(argc != 2 ) {
        fprintf(stderr, "Usage : %s [IP] or [Domain]\n", argv[0]);
        return 1;
    }

    if( isValidIpAddress(argv[1]) !=0 ){
        memset(&addr, 0, sizeof(addr));

        addr.sin_addr.s_addr=inet_addr(argv[1]);
        hostent=gethostbyaddr((char*)&addr.sin_addr, 4, AF_INET);

        if(!hostent) {
            perror("invalid host!!");
            return 1;
        } 
    } else {
        hostent = gethostbyname(argv[1]);

        if(hostent == NULL) {
            perror("invalid dns!!");
            return 1;
        }
    }

    printHostent(hostent);
    return 0;
}

