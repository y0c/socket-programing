#include "db.h"

void save_hashtable(FILE* fp, hashtable_t * hashtable) {
    int i;
    entry_t *first;
    char* record_data;
    fp = fopen("dns.db", "w");

    for(i = 0 ; i < hashtable->size; i ++ ){
        first = hashtable->table[i];
        while(first != NULL ) {
            record_data = (char*)calloc(strlen(first->key)+strlen(first->value)+100, sizeof(char));
            sprintf(record_data,"%s#%s\n", first->key, first->value);
            if( strlen(record_data) > 1) {
                fputs(record_data, fp);
                fflush(fp);
            }
            first = first->next;
        }
    }

    fclose(fp);
}

void insert_dns_record(FILE*fp, char* query, char* data) {
    char* record_data;
    fp = fopen("dns.db", "a+");
    record_data = (char*)calloc(strlen(query)+strlen(data)+100, sizeof(char));
    sprintf(record_data,"%s#%s\n", query, data);
    fputs(record_data, fp);
    fflush(fp);
    fclose(fp);
}

hashtable_t* load_db(FILE* fp) {
    hashtable_t* hashtable = ht_create(65000);
    char buffer[1000];
    char* query;
    char** read_data;

    while(!feof(fp) && fgets(buffer,1000,fp)) {
        read_data = str_split(buffer,"#");
        str_rmchr(read_data[1], '\n');
        ht_set(hashtable, read_data[0], read_data[1]);
    }
    return hashtable;
}
