#include "db.h"

void save_hashtable(FILE* fp, hashtable_t * hashtable) {
    int i;
    entry_t *first;
    char* record_data;

    for(i = 0 ; i < hashtable->size; i ++ ){
        first = hashtable->table[i];
        while(first != NULL ) {
            record_data = (char*)malloc(strlen(first->key)+strlen(first->value)+1);
            sprintf(record_data,"%s#%s\n", first->key, first->value);
            fputs(record_data, fp);
            fflush(fp);
            first = first->next;
        }
    }

    rewind(fp);
}

hashtable_t* load_db(FILE* fp) {
    hashtable_t* hashtable = ht_create(65000);
    char buffer[1000];
    char* query;
    char** read_data;

    while(!feof(fp) && fgets(buffer,1000,fp)) {
        read_data = str_split(buffer,"#");
        read_data[1][strlen(read_data[1])-1] = '\0';
        ht_set(hashtable, read_data[0], read_data[1]);
    }
    return hashtable;
}
