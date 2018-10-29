#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "logger.h"
#define MAXBUF 1024

char* str_reverse(char* buf) {
    int len = strlen(buf);
    char* temp = malloc(sizeof(char)* len);
    int i = 0;

    for( i = 0 ; i < len ; i ++ ) {
        temp[i] = buf[len-i -1];
    }

    temp[i] = 0;
    return temp;
}

int main(int argc, char ** argv) {
    int server_sockfd, client_sockfd;
    int client_len, n;
    char buf[MAXBUF];
    char message[200];
    struct sockaddr_in  clientaddr, serveraddr;
    pid_t pid;

    client_len = sizeof(clientaddr);
    log_init();

    if((server_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1 ) {
        perror("socket error : ");
        log_write(ERROR, "socket error!");
        exit(0);
    }

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(atoi(argv[1]));

    bind(server_sockfd, (struct sockaddr * )&serveraddr, sizeof(serveraddr));
    listen(server_sockfd, 5);

    while(1)
    {
        memset(buf, 0x00, MAXBUF);

        client_sockfd = accept(server_sockfd, (struct sockaddr *)&clientaddr, &client_len);

        if (client_sockfd == -1 ) {
            continue;
        } else {
            sprintf(message," New Client Connect : %s", inet_ntoa(clientaddr.sin_addr));
            log_write(INFO, message);
        }

        pid=fork();

        if(pid == -1){
            close(client_sockfd);
        }

        if(pid == 0 ) {
            close(server_sockfd);

            while(1) {

                if( (n=read(client_sockfd, buf, MAXBUF)) <= 0 ){
                    close(client_sockfd);
                    continue;
                }

                if(strncmp("exit", buf,4) == 0) {
                    break;
                }

                if( write(client_sockfd, str_reverse(buf), MAXBUF) <= 0){
                    perror("write error : ");
                    //error log
                    log_write(ERROR, "write error!");
                    close(client_sockfd);
                }

                sprintf(message,"Original String : %s", buf);
                log_write(INFO, message);

                sprintf(message,"Reverse String : %s", str_reverse(buf));
                log_write(INFO, message);

            }
            close(client_sockfd);
            sprintf(message,"Client Disconnect : %s", inet_ntoa(clientaddr.sin_addr));
            log_write(INFO, message);
            return 0;

        } else {
            close(client_sockfd);
        }

    }

    log_destory();
    return 0;
}
