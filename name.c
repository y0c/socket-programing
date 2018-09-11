#include <stdio.h>

int main() {
    char name[30];

    FILE *fp;
    fp=fopen("a.dat", "w");

    gets(name);

    printf("Name is : %s \n", name);
    fprintf(fp, name, fp);
    fclose(fp);

    return 0;
}