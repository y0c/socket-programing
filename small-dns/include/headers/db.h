#ifndef DB_H
#define DB_H
#include "common.h"
#include "hashtable.h"

//DNS Record 삽입 함수
void insert_dns_record(char* query, char* data);
//DNS Record 수정 함수
void update_dns_record(char* query, char* data);
//File 에서 정보를 로딩해서 hashtable을 생성
hashtable_t* load_db();
void save_hashtable(hashtable_t * hashtable);
//파일이 존재하는지 확인
int file_exists(const char *fname);
#endif
