#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define MAXLINE 512

int get_file_size(int fd) {
    // fd = fileno(f); //if you have a stream (e.g. from fopen), not a file descriptor.
    int size;
    struct stat buf;
    fstat(fd, &buf);
    size = buf.st_size;
    return size;
}

int main(int argc, char ** argv) {

    int source_fd;
    int dest_fd;
    int readn;
    int totaln=0;
    char buf[MAXLINE];

    if( argc != 3 ) {
        fprintf(stderr, "Usage : %s [source file] [dest file] \n", argv[0]);
        return 1;
    }

    if( !(source_fd = open(argv[1], O_RDONLY)) ) {
        perror("Error ");
        return 1;
    }

    if( !(dest_fd = open(argv[2], O_CREAT | O_EXCL | O_WRONLY,
        S_IRUSR| S_IWUSR | S_IRGRP | S_IROTH ))) {
        perror("Error ");
        return 1;        
    }

    if( errno == EEXIST ) {
        perror("Error");
        close(dest_fd);
        return 1;
    }

    memset(buf, 0x00, MAXLINE);
    while((readn= read(source_fd, buf, MAXLINE)) > 0 ) {
        printf("readn : %d\n", readn);
        totaln+=write(dest_fd, buf, readn);
        memset(buf, 0x00, MAXLINE);
    }

    printf("Total Copy Size : %d\n", totaln);

    int src_size = get_file_size(source_fd);
    int dest_size = get_file_size(dest_fd);

    printf("Source File size : %d\n", src_size);
    printf("Dest File size : %d\n", dest_size);

    if( src_size == dest_size ) {
        printf("File Copy Success!");
    } else { 
        printf("File Size Mismatch : source %d dest %d\n", src_size, dest_size);
    }

    close(source_fd);
    close(dest_fd);

    return 0;
}