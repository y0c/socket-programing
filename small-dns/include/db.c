#include "db.h"


/**
 * Function: insert_dns_record
 * File DB에 DNS Record 추가
 * --------------------------------------
 *  char*query: 검색한 query
 *  char*data: 검색결과를 직렬화한 문자열
 *  File에 기록은
 *  검색Key#검색결과 의 형태로 저장하게된다.
 */
void insert_dns_record(char* query, char* data) {
    char* record_data;
    FILE* fp = fopen("dns.db", "a+");
    record_data = (char*)calloc(strlen(query)+strlen(data)+100, sizeof(char));
    sprintf(record_data,"%s#%s\n", query, data);
    fputs(record_data, fp);
    fflush(fp);
    fclose(fp);
}

/**
 * Function: update_dns_record
 * File DB에 특정 query로 검색하여 hit를 update한다.
 * --------------------------------------
 *  char*query: 검색한 query
 *  char*data: 검색결과를 직렬화한 문자열
 */
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

/**
 * Function: load_db
 * File DB에서 해쉬테이블(메모리)로 데이터 로딩
 * --------------------------------------
 */
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

/**
 * Function: file_exists
 * File이 있는지 체크
 * --------------------------------------
 *  char*fname: 파일명
 *  return : true or false
 */
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
