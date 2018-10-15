#include "str.h"

/**
 * Function: str_rmchr
 * 문자열에서 특정문자를 제거한다.
 * Call by Reference
 * --------------------------------------
 *  str: 문자열
 *  chr: 제거할 문자
 */
void str_rmchr(char *s, char chr)
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
/**
 * Function: str_sep
 * 문자열을 토큰단위로 분리한다. strtok에서 NULL처리 추가
 * --------------------------------------
 *  stringp: 문자열 리스트
 *  delim: 토큰
 */
char *str_sep(char **stringp, const char *delim)
{

    char *ptr = *stringp;

    if(ptr == NULL) {
        return NULL;
    }

    while(**stringp) {
        if(strchr(delim, **stringp) != NULL) {
            **stringp = 0x00;
            (*stringp)++;
            return ptr;
        }
        (*stringp)++;
    }

    *stringp = NULL;
    return ptr;
}

/**
 * Function: str_split
 * 문자열을 토큰단위로 분리해서 리스트로 만듬
 * --------------------------------------
 *  str: 분리할 문자열
 *  delim: 구분자
 */
char** str_split(const char* str, const char* delim)
{
    char** result;
    char* tmp;
    char* tmp1;
    int cnt = 1;
    int idx = 0;
    char* token;

    if( str == NULL ) {
        return NULL;
    }

    tmp = (char*) calloc(strlen(str),sizeof(char));
    strncpy(tmp,str,strlen(str));

    tmp1 = (char*) calloc(strlen(str),sizeof(char));
    strncpy(tmp1,str,strlen(str));

    while ((token = str_sep(&tmp, delim)) != NULL) {
        cnt++;
    }

    result = (char**)calloc(cnt,sizeof(char*));

    while ((token = str_sep(&tmp1, delim)) != NULL) {
        result[idx] = (char*)calloc(strlen(token),sizeof(char*));
        strncpy(result[idx++],token,strlen(token));
    }

    return result;
}

/**
 * Function: str_join
 * 문자열 리스트를 delim으로 구분지어서 연결
 * --------------------------------------
 */
char* str_join(char** str, char* delim)
{
    char* result = (char*)calloc(10,sizeof(char));
    char** tmp = str;

    while(*tmp != NULL){
        result = str_add(result, *tmp);

        if( *(tmp+1) != NULL ){
            result = str_add(result, delim);
        }
        tmp++;
    }

    return result;
}

/**
 * Function: str_add
 * 두개의 문자열을 합쳐서 새로운 문자열 리턴
 * --------------------------------------
 */
char* str_add(char* str1, char* str2) {
    char* result;

    if((result = (char*)calloc(strlen(str1) + strlen(str2)+1,sizeof(char))) != NULL) {
        result[0] = '\0';
        strcat(result,str1);
        strcat(result,str2);
    } else {
        result = NULL;
    }

    return result;
}
