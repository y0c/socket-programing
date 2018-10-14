#include "str.h"

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

char** str_split(const char* str, const char* delim)
{
    char** result;
    char* tmp;
    int cnt = 1;
    int idx = 0;
    char* token;

    if( str == NULL ) {
        return NULL;
    }

    tmp = (char*) calloc(strlen(str),sizeof(char));
    strcpy(tmp,str);

    while ((token = str_sep(&tmp, delim)) != NULL) {
        cnt++;
    }

    result = (char**)calloc(cnt,sizeof(char*));

    free(tmp);
    tmp = (char*) calloc(strlen(str),sizeof(char));

    strcpy(tmp,str);
    while ((token = str_sep(&tmp, delim)) != NULL) {
        result[idx] = (char*)calloc(strlen(token),sizeof(char*));
        strcpy(result[idx++],token);
    }

    free(tmp);
    return result;
}

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
