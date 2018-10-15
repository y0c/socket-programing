#ifndef STRING_H
#define STRING_H
#include <string.h>
#include <stdlib.h>
// 문자열에서 특정 문자 제거
void str_rmchr(char *s, char chr);
// delim토큰을 통해서 문자열리스트를 연결된 문자열로 만듬 ex) 111.111.22.33,22,22,11,22
char* str_join(char** str, char* delim);
// strtok 라이브러리 함수와 비슷한 역활을 수행 단 NULL처리 기능을 추가
char *str_sep(char **stringp, const char *delim);
//  delim토큰을 통해서 문자열을 쪼개서 리스트로 만듬
char** str_split(const char* str, const char* delim);
// 문자열 두개를 더해서 합쳐진 문자열을 리턴
char* str_add(char* str1, char* str2);

#endif
