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


void query_to_server(int sockfd, struct sockaddr_in serv_adr, struct sockaddr_in from_adr, char* query) {
    host_data *hostdata;
    sock_data sdata;
    socklen_t adr_sz;

    strcpy(sdata.body, query);
    sendto(sockfd, (void*) &sdata, sizeof(sdata), 0, (struct sockaddr*) &serv_adr, sizeof(serv_adr));

    adr_sz = sizeof(from_adr);
    memset(&sdata, 0, sizeof(sdata));
    recvfrom(sockfd, (void*)&sdata, sizeof(sdata), 0, (struct sockaddr*)&from_adr, &adr_sz);


    if( sdata.status == INVALID_IP ) {
        printf("Invalid IP !!!\n");
    } else if( sdata.status == INVALID_DNS ) {
        printf("Invalid DNS !!!\n");
    } else {
        hostdata = deserialize(sdata.body);
        print_host_ent(hostdata);
    }
}

void load_from_file(int sockfd, struct sockaddr_in serv_adr, struct sockaddr_in from_adr) {
    FILE* fp = fopen("dnslist.txt", "r+");
    char buffer[1000];

    while(!feof(fp) && fgets(buffer,1000,fp)) {

        str_rmchr(buffer, '\n');
        query_to_server(sockfd, serv_adr, from_adr, buffer);
    }
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
    struct sockaddr_in serv_adr, from_adr;
    char input[200];

    if( argc < 2 ) {
        printf("Input Server IP Address");
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


    if(argc == 2 ) {
        while(1) {
            printf("> Input Query(DNS or IP) : ");
            fgets(input, 200, stdin);
            input[strlen(input)-1]= '\0';

            if( strncmp(input, "quit", 4) == 0 ) {
                return 0;
            } else {
                query_to_server(sockfd, serv_adr, from_adr, input);
            }
        }
    } else if ( argc == 3 ) {
        query_to_server(sockfd, serv_adr, from_adr, argv[2]);
    }



    close(sockfd);
    return 0;
}
