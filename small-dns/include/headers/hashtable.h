#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

//Hash Node 구조체
struct entry_s {
	char *key;
	char *value;
	struct entry_s *next;
};

typedef struct entry_s entry_t;

//HashTable 구조체 Node의 2차원배열로 구성
struct hashtable_s {
	int size;
	struct entry_s **table;
};

typedef struct hashtable_s hashtable_t;


/* 해쉬 테이블 생성 */
hashtable_t *ht_create( int size );

/* 해쉬 함수 */
int ht_hash( hashtable_t *hashtable, char *key );


/* 해쉬 노드 삽입  */
void ht_set( hashtable_t *hashtable, char *key, char *value );

/* 해쉬 노드 검색 */
char *ht_get( hashtable_t *hashtable, char *key );

/* 해쉬 노드 출력*/
void ht_print(hashtable_t* hashtable);

#endif
