#include "hashtable.h"


/**
 * Function: ht_create
 * hashtable을 생성
 * --------------------------------------
 *  size: table size
 *  return: hashtable
 */
hashtable_t *ht_create( int size ) {

	hashtable_t *hashtable = NULL;
	int i;

	if( size < 1 ) return NULL;

	if( ( hashtable = malloc( sizeof( hashtable_t ) ) ) == NULL ) {
		return NULL;
	}

	if( ( hashtable->table = malloc( sizeof( entry_t * ) * size ) ) == NULL ) {
		return NULL;
	}
	for( i = 0; i < size; i++ ) {
		hashtable->table[i] = NULL;
	}

	hashtable->size = size;

	return hashtable;
}

/**
 * Function: ht_create
 * hashtable을 생성
 * --------------------------------------
 *  size: table size
 *  return: hashtable
 */
int ht_hash( hashtable_t *hashtable, char *key ) {

	unsigned long int hashval;
	int i = 0;

	while( hashval < ULONG_MAX && i < strlen( key ) ) {
		hashval = hashval << 8;
		hashval += key[ i ];
		i++;
	}

	return hashval % hashtable->size;
}

/**
 * Function: ht_newpair
 * hashnode를 생성해서 리턴
 * --------------------------------------
 */
entry_t *ht_newpair( char *key, char *value ) {
	entry_t *newpair;

	if( ( newpair = malloc( sizeof( entry_t ) ) ) == NULL ) {
		return NULL;
	}

	if( ( newpair->key = strdup( key ) ) == NULL ) {
		return NULL;
	}

	if( ( newpair->value = strdup( value ) ) == NULL ) {
		return NULL;
	}

	newpair->next = NULL;

	return newpair;
}

/**
 * Function: ht_set
 * hashtable에 노드를 추가한다.
 * --------------------------------------
 *  hashtable: 추가할 hashtable
 */
void ht_set( hashtable_t *hashtable, char *key, char *value ) {
	int bin = 0;
	entry_t *newpair = NULL;
	entry_t *next = NULL;
	entry_t *last = NULL;

	bin = ht_hash( hashtable, key );

	next = hashtable->table[ bin ];

	while( next != NULL && next->key != NULL && strcmp( key, next->key ) > 0 ) {
		last = next;
		next = next->next;
	}

	if( next != NULL && next->key != NULL && strcmp( key, next->key ) == 0 ) {
        printf("%s\n", value);

		free( next->value );
		next->value = strdup( value );

	} else {
		newpair = ht_newpair( key, value );

		if( next == hashtable->table[ bin ] ) {
			newpair->next = next;
			hashtable->table[ bin ] = newpair;

		} else if ( next == NULL ) {
			last->next = newpair;

		} else  {
			newpair->next = next;
			last->next = newpair;
		}
	}
}

/**
 * Function: ht_get
 * 해쉬테이블에서 key로 검색한 데이터 리턴
 * --------------------------------------
 */
char *ht_get( hashtable_t *hashtable, char *key ) {
	int bin = 0;
	entry_t *pair;

	bin = ht_hash( hashtable, key );

	pair = hashtable->table[ bin ];
	while( pair != NULL && pair->key != NULL && strcmp( key, pair->key ) > 0 ) {
		pair = pair->next;
	}

	if( pair == NULL || pair->key == NULL || strcmp( key, pair->key ) != 0 ) {
		return NULL;

	} else {
		return pair->value;
	}

}


/**
 * Function: ht_print
 * 해쉬테이블에 있는 모든 데이터 출력
 * --------------------------------------
 */
void ht_print(hashtable_t *hashtable) {
    int i;
    entry_t *first;

    for(i = 0 ; i < hashtable->size; i ++ ){
        first = hashtable->table[i];
        while(first != NULL ) {
            printf("%s %s\n", first->key, first->value);
            first = first->next;
        }
    }
}
