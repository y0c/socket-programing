#include "common.h"
#include "hashtable.h"
#include "str.h"
#include "db.h"

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



void savetest() {

    FILE* fp = fopen("dns.db", "w+");

    char* get;
    hashtable_t *hashtable = ht_create(65000);
    char *domains[] = {
        "naver.com",
        "www.naver.com",
        "daum.com",
        "www.daum.com",
        "amazone.com",
        "trello.com",
        "facebook.com",
        "smartncs.co.kr",
        "google.co.kr",
        "hs.ac.kr",
        "apple.com",
        "mail.naver.com",
        "slack.com",
        "melon.com",
        "github.com",
        "gitlab.com",
        "ebs.com",
        "ebs.co.kr",
        "gabia.com",
        "docker.io",
        "stackoverflow.com",
    };
    int i = 0;

    for(i = 0 ; i < 20; i++ ){
        struct hostent* hostent = gethostbyname(domains[i]);
        host_data* hostdata = (host_data*)malloc(sizeof(host_data));

        hostdata->h_name = hostent->h_name;
        hostdata->h_addrtype = hostent->h_addrtype;
        hostdata->h_length = hostent->h_length;
        hostdata->h_aliases = convert_addr(hostent->h_aliases);
        hostdata->h_addr_list = convert_addr(hostent->h_addr_list);
        hostdata->hit = 0;

        ht_set(hashtable, domains[i], serialize(hostdata));
        save_hashtable(fp, hashtable);

        get = ht_get(hashtable, domains[i]);

        if(get == NULL ) {
            printf("#####################");
            printf("%s\n", domains[i]);
        } else {
            hostdata = deserialize(get);
            hostdata->hit = hostdata->hit+1;
            ht_set(hashtable, domains[i], serialize(hostdata));
            save_hashtable(fp, hashtable);;
        }




        //printf("%s\n", serialize(hostdata));
        //
        /*
        printf("Print no join\n");
        while(*hostdata->h_aliases != NULL ) {
            printf("%s\n", *hostdata->h_aliases);
            hostdata->h_aliases++;
        }

        while(*hostdata->h_addr_list != NULL ) {
            printf("%s\n", *hostdata->h_addr_list);
            hostdata->h_addr_list++;
        }
        */

        /*
        printf("Print Join After\n");

        printf("%s\n", str_join(hostdata->h_aliases, ","));
        printf("%s\n", str_join(hostdata->h_addr_list, ","));
        */
    }
}

void loadtest() {
    FILE* fp = fopen("dns.db", "r+");
    hashtable_t* hashtable = load_db(fp);
    ht_print(hashtable);
}
void remchar(char *s, char chr)
{
   int i, j = 0;
   for ( i = 0; s[i] != '\0'; i++ ) /* 'i' moves through all of original 's' */
   {
      if ( s[i] != chr )
      {
         s[j++] = s[i]; /* 'j' only moves after we write a non-'chr' */
      }
   }
   s[j] = '\0'; /* re-null-terminate */
}
int main(void){

    //savetest();
  //
  //
  /*
    struct hostent* hostent = gethostbyname("www.naver.com");

    hashtable_t* table = ht_create(1000);
    host_data* hostdata = (host_data*)malloc(sizeof(host_data));
    char* get;

    hostdata->h_name = hostent->h_name;
    hostdata->h_addrtype = hostent->h_addrtype;
    hostdata->h_length = hostent->h_length;
    hostdata->h_aliases = convert_addr(hostent->h_aliases);
    hostdata->h_addr_list = convert_addr(hostent->h_addr_list);
    hostdata->hit = 0;


    ht_set(table,"www.naver.com", serialize(deserialize(serialize(hostdata))));

    get = ht_get(table,"www.naver.com");

    printf("%s\n", serialize(deserialize(get)));
    */

    FILE* fp = fopen("test.txt","wb+");

    fprintf(fp,"test\n");
    fprintf(fp,"test\n");
    fprintf(fp,"test\n");


    rewind(fp);
    fprintf(fp, "%d\n",2323434);
    fclose(fp);
}
