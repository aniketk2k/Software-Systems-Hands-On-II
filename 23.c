/*

Name: 23.c
Author: Aniket Kumar
Decsription: Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).
Date: September 28th, 2025

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    long long max_files = sysconf(_SC_OPEN_MAX);
    printf("Maximum number of files a process can open: %lld\n", max_files);

    int fd[2];
    pipe(fd);
    long long pipe_size = fpathconf(fd[0], _PC_PIPE_BUF);

    printf("Size of pipe(i.e. circular buffer): %lld\n", pipe_size);

    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc -o temp 23.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
Maximum number of files a process can open: 1024
Size of pipe(i.e. circular buffer): 4096

*/