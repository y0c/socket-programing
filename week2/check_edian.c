#include <stdio.h>

#define BIG 0 
#define LITTLE 1

int check_edian(void);

int main(int argc, char ** argv) {
    int edian;
    edian = check_edian();
    if(edian == LITTLE) {
        printf("little edian\n");
    } else {
        printf("big edian\n");
    }

    return 0;
}

int check_edian(void) {
    int i = 0x00000001;
    return ((char*)&i)[0]?LITTLE:BIG;
}