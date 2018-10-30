#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/ipc.h>

int main(int argc, char ** argv) {
    key_t keyval = 2345;
    int shmid;
    shmid = shmget(keyval, 1024, IPC_CREAT | 0666);
    if(shmid == -1 ) {
        printf("shm Create failure\n");
        return 1;
    }

    printf("shm Create Success!\n");
    return 0;
}
