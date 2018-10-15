
#include "common.h"
#include "hashtable.h"
#include "db.h"


int main(int argc, char* argv[]) {
    int sockfd;
    sock_data sdata;
    char message[300];
    char* query;
    char* data;
    socklen_t adr_sz;
    host_data *hostdata;
    struct sockaddr_in addr, cliaddr, hostaddr;
    struct hostent *hostent;
    FILE* fp_log = fopen("server.log", "a+");
    hashtable_t *hashtable = ht_create(HASHTABLE_MAX);

    //dns db가 존재하면 File DB에서 메모리로 로딩
    if( file_exists("dns.db") ) {
        hashtable = load_db();
    }

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

        //Client 정보 Log 출력
        sprintf(message,"Client Info : %s (%d)", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
        log_write(fp_log, INFO, message);

        sprintf(message,"Query : %s", sdata.body);
        log_write(fp_log, INFO, message);

        query = (char*)calloc((sizeof(char))* (strlen(sdata.body)+1),1);
        strcpy(query, sdata.body);

        hostdata = (host_data*) calloc(1,sizeof(host_data));

        sdata.status = SUCCESS;

        //해쉬테이블에 query가 존재하면 hit+1 , 그렇지않으면 dns record삽입
        if((data=ht_get(hashtable,query)) == NULL) {

            if(is_valid_ip_address(query)) {
                memset(&hostaddr, 0, sizeof(hostaddr));

                hostaddr.sin_addr.s_addr = inet_addr(query);
                hostent = gethostbyaddr((char*)&hostaddr.sin_addr, 4, AF_INET);

                if(hostent == NULL) {
                    sdata.status = INVALID_IP;
                    log_write(fp_log, ERROR, "Invalid IP !!");
                }
            } else {
                hostent = gethostbyname(query);

                if(hostent == NULL){
                    sdata.status = INVALID_DNS;
                    log_write(fp_log, ERROR, "Invalid DNS !!");
                }
            }


            //정상적으로 DNS결과를 가져온경우
            if( sdata.status == SUCCESS ) {
                hostdata->h_name = hostent->h_name;
                hostdata->h_addrtype = hostent->h_addrtype;
                hostdata->h_length = hostent->h_length;
                hostdata->h_aliases = hostent->h_aliases;
                hostdata->h_addr_list = convert_addr(hostent->h_addr_list);
                hostdata->hit = 1;

                sprintf(message,"Result : %s ", serialize(hostdata));
                log_write(fp_log, INFO, message);

                //데이터를 직렬화해서 네트워크, 파일에 각각 write
                data = serialize(hostdata);
                ht_set(hashtable,query,data);
                insert_dns_record(query, data);
            }
        } else {
            hostdata = deserialize(data);
            hostdata->hit = hostdata->hit+1;

            data = serialize(hostdata);
            ht_set(hashtable,query,data);
            update_dns_record(query, data);
        }

        if( sdata.status == SUCCESS ) {
            strcpy(sdata.body, data);
            sdata.body[strlen(data) + 1] = '\0';
            sdata.content_length = strlen(data);
        }

        free(hostdata);
        free(query);


        //data 전송
        sendto(sockfd, (void*)&sdata, sizeof(sdata),0,(struct sockaddr*)&cliaddr, adr_sz);

    }
}
