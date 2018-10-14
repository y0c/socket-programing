#include "db.h"

void save_hashtable(hashtable_t * hashtable) {
    int i;
    entry_t *first;
    char* record_data;
    FILE* fp = fopen("dns.db", "w+");

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

void insert_dns_record(char* query, char* data) {
    char* record_data;
    FILE* fp = fopen("dns.db", "a+");
    record_data = (char*)calloc(strlen(query)+strlen(data)+100, sizeof(char));
    sprintf(record_data,"%s#%s\n", query, data);
    fputs(record_data, fp);
    fflush(fp);
    fclose(fp);
}

void update_dns_record(char* query, char* data) {
    char buffer[1000];
    char** read_data;
    FILE* fp = fopen("dns.db", "r+");
    while(!feof(fp) && fgets(buffer,1000,fp)) {
        read_data = str_split(buffer,"#");
        str_rmchr(read_data[1], '\n');
        if( strcmp(read_data[0], query) == 0 ){
            fseek(fp, (strlen(read_data[1])+1) *-1,SEEK_CUR);
            fprintf(fp,"%s\n", data);
        }
    }
}

hashtable_t* load_db() {
    hashtable_t* hashtable = ht_create(65000);
    char buffer[1000];
    char* query;
    char** read_data;
    FILE* fp = fopen("dns.db", "r+");

    while(!feof(fp) && fgets(buffer,1000,fp)) {
        read_data = str_split(buffer,"#");
        str_rmchr(read_data[1], '\n');
        ht_set(hashtable, read_data[0], read_data[1]);
    }
    return hashtable;
}

int file_exists(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}
