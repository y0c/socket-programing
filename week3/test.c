#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>

void info_addr(struct hostent *a)
{
    printf("Official name : %s\n",a->h_name);
    printf("Host type : %s\n",(a->h_addrtype==AF_INET)?"AF_INET4" : "AF_INET6");
    printf("Addr length : %d\n",a->h_length);

    while(*a->h_aliases !=NULL)
    {
        printf("aliases : %s\n",inet_ntoa(*(struct in_addr *)*a->h_aliases));
        a->h_aliases++;
    }
   
    while(*a->h_addr_list !=NULL)
    {
        printf("Addr_list : %s\n",inet_ntoa(*(struct in_addr *)*a->h_addr_list));
        a->h_addr_list++;
    }   
}

int main(int argc, char **argv)
{
    struct hostent    *myent;
    struct sockaddr_in addr;
   
    if(argc !=2)
    {
        fprintf(stderr,"Usage : %s [domain name] or [IP]\n",argv[0]);
        return 1;
    }

        memset(&addr, 0, sizeof(addr));
        addr.sin_addr.s_addr = inet_addr(argv[1]);
        myent = gethostbyaddr((char*)&addr.sin_addr, 4, AF_INET);
        printf("Official name : %s\n",myent->h_name);
        if(!myent)
            perror("gethost....error");
        info_addr(myent);
   
    return 0;
} 