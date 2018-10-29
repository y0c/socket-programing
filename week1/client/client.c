#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>

#define MAX_LINE 1024

int main(int argc, char ** argv) {
    struct sockaddr_in serveraddr;
    int server_sockfd;
    int clinet_len;
    char buf[MAX_LINE];
    int len;

    if((server_sockfd = socket(AF_INET, SOCK_STREAM, 0 )) == -1 ) {
        perror("error : ");
        exit(0);
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
    serveraddr.sin_port = htons(atoi(argv[2]));

    clinet_len = sizeof(serveraddr);

    if(connect(server_sockfd, (struct sockaddr*)&serveraddr, clinet_len) == -1 ) {
        perror("connect error : ");
        return 1;
    }

    while(1){
        memset(buf, 0x00, MAX_LINE);
        read(0, buf, MAX_LINE);

        len = strlen(buf);
        buf[len-1] = 0;

        if( write(server_sockfd, buf, MAX_LINE) <= 0 ) {
            perror("write error : ");
            return 1;
        }

        if(strncmp(buf, "exit",4) == 0) {
            break;
        }

        memset(buf, 0x00, MAX_LINE);
        if( read(server_sockfd, buf, MAX_LINE) <=0 ) {
            perror("read error : ");
            return 1;
        }



        printf("%s\n", buf);

    }

    close(server_sockfd);


    return 0;
}
