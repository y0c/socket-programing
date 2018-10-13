#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    char* a;
    char* test = "werewrew";
    a = (char*)malloc(strlen(test));
    strcpy(a, test);
    printf("%s", a);
}
