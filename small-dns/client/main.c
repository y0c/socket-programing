#include "common.h"

void print_host_ent(host_data *hd) {
    printf("Official name : %s\n", hd->h_name);
    printf("Host Type : %s\n", hd->h_addrtype==AF_INET ? "ipv4" : "ipv6");
    printf("Host Length : %d\n", hd->h_length);

    printf("Host Aliases\n");
    while(*hd->h_aliases != NULL ){
        printf("%s\n",  *hd->h_aliases);
        hd->h_aliases++;
    }

    printf("Host Addr List\n");
    while(*hd->h_addr_list != NULL ){
        printf("%s\n", *hd->h_addr_list);
        hd->h_addr_list++;
    }
    printf("Hit: %d\n", hd->hit);
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
    host_data *hostdata;
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
    serv_adr.sin_port = htons(PORT);

    strcpy(sdata.body, argv[2]);
    sendto(sockfd, (void*) &sdata, sizeof(sdata), 0, (struct sockaddr*) &serv_adr, sizeof(serv_adr));

    adr_sz = sizeof(from_adr);
    memset(&sdata, 0, sizeof(sdata));
    recvfrom(sockfd, (void*)&sdata, sizeof(sdata), 0, (struct sockaddr*)&from_adr, &adr_sz);

    hostdata = deserialize(sdata.body);
    print_host_ent(hostdata);

    close(sockfd);
    return 0;
}
