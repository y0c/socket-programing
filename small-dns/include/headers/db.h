#ifndef DB_H
#define DB_H
#include "common.h"
#include "hashtable.h"

void insert_dns_record(char* query, char* data);
hashtable_t* load_db();
void save_hashtable(hashtable_t * hashtable);
int file_exists(const char *fname);
void update_dns_record(char* query, char* data);
#endif
