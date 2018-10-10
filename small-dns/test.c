#include <stdio.h>

int validateIP(char *ipadd)
{
    int a[4];
    int i;
    int rc = sscanf(ipadd, "%d.%d.%d.%d", &a[0], &a[1], &a[2], &a[3]);
    if (rc < 4) return 0;
    for(i = 0; i < 4; i ++ )
        if(a[i] > 255 || a[i] <= 0 ) return 0;

    return 1;
}
int main() {
    char* ip = "12.13.14.15523423423423423";
    printf("%d", validateIP(ip));
	return 0;
}
