#include "common.h"
#include "hashtable.h"
#include "str.h"
#include "db.h"

int insert_dns_record(FILE* fp, char* query, host_data* record) {
    char* data = serialize(record);
    host_data* temp = (host_data*)malloc(sizeof(host_data));
    char* record_data = (char*)malloc(strlen(data)+strlen(query)+1);

    sprintf(record_data,"%s#%s\n", query, data);
}


void savetest() {

    FILE* fp = fopen("dns.db", "w+");

    hashtable_t *hashtable = ht_create(65000);
    char *domains[] = {
        "naver.com",
        "naver.com",
        "naver.com",
        "naver.com",
        "www.naver.com",
        "google.co.kr",
        "hs.ac.kr",
        "facebook.com",
        "smartncs.co.kr"
    };
    int i = 0;

    for(i = 0 ; i < 9 ; i ++ ){
        struct hostent* hostent = gethostbyname(domains[i]);
        host_data* hostdata = (host_data*)malloc(sizeof(host_data));

        hostdata->h_name = hostent->h_name;
        hostdata->h_addrtype = hostent->h_addrtype;
        hostdata->h_length = hostent->h_length;
        hostdata->h_aliases = hostent->h_aliases;
        hostdata->h_addr_list = hostent->h_addr_list;
        hostdata->hit = 0;

        ht_set(hashtable, domains[i], serialize(hostdata));
        save_hashtable(fp, hashtable);
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

    savetest();
}
