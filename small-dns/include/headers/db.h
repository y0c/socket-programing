#ifndef DB_H
#define DB_H
#include "common.h"
#include "hashtable.h"

hashtable_t* load_db(FILE* fp);
void save_hashtable(FILE* fp, hashtable_t * hashtable);
#endif
