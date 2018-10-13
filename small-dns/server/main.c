
#include "common.h"
#include "hashtable.h"
#include "db.h"


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
    char* query;
    char* data;
    socklen_t adr_sz;
    host_data *hostdata;
    struct sockaddr_in addr, cliaddr, hostaddr;
    struct hostent *hostent;
    FILE* fp = fopen("dns.db", "r+");
    hashtable_t *hashtable = load_db(fp);

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

        query = (char*)malloc((sizeof(char))* strlen(sdata.body));
        strcpy(query, sdata.body);

        hostdata = (host_data*) malloc(sizeof(host_data));

        if((data=ht_get(hashtable,query)) == NULL) {

            if(is_valid_ip_address(query)) {
                memset(&hostaddr, 0, sizeof(hostaddr));

                hostaddr.sin_addr.s_addr = inet_addr(query);
                hostent = gethostbyaddr((char*)&hostaddr.sin_addr, 4, AF_INET);

                if(hostent == NULL) {
                    printf("invalid host\n");
                }
            } else {
                hostent = gethostbyname(query);

                if(hostent == NULL){
                    printf("invalid DNS\n");
                }
            }

            hostdata->h_name = hostent->h_name;
            hostdata->h_addrtype = hostent->h_addrtype;
            hostdata->h_length = hostent->h_length;
            hostdata->h_aliases = convert_addr(hostent->h_aliases);
            hostdata->h_addr_list = convert_addr(hostent->h_addr_list);
            hostdata->hit = 0;

            data = serialize(hostdata);
            ht_set(hashtable, query, data);
        } else {
            hostdata = deserialize(data);
            hostdata->hit = hostdata->hit+1;

            data = serialize(hostdata);
            ht_set(hashtable,query,data);
            fp = fopen("dns.db", "w");
            save_hashtable(fp, hashtable);
        }

        free(hostdata);
        free(query);

        strcpy(sdata.body, data);
        sdata.body[strlen(data) + 1] = '\0';
        sdata.content_length = strlen(data);

        sendto(sockfd, (void*)&sdata, sizeof(sdata),0,(struct sockaddr*)&cliaddr, adr_sz);

    }
}
