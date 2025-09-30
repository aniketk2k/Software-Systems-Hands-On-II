/*

Name: 3.c
Author: Aniket Kumar
Decsription: Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: September 30th, 2025

Point to Remember:
    rlim_cur is softlimit where the kernel enforces the valur on the process
    rlim_max is hardlimit where only root can work on it, also it is the ceiling for softlink
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <errno.h>

int main(){
    struct rlimit limit;

    if(getrlimit(RLIMIT_NOFILE, &limit) == -1){
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    printf("Current limits on open files:\n");
    printf("Soft = %ld, Hard = %ld\n", (long)limit.rlim_cur, (long)limit.rlim_max);

    limit.rlim_cur = 4096;    // new soft limit
    // limit.rlim_max = 8192; // to change the hard limit (requires root)

    if(setrlimit(RLIMIT_NOFILE, &limit) == -1){
        perror("setrlimit");
        exit(EXIT_FAILURE);
    }
    
    if(getrlimit(RLIMIT_NOFILE, &limit) == -1){
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    printf("New limits on open files:\n");
    printf("Soft = %ld, Hard = %ld\n", (long)limit.rlim_cur, (long)limit.rlim_max);

    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc -o temp 3.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
Current limits on open files:
Soft = 1024, Hard = 1048576
New limits on open files:
Soft = 4096, Hard = 1048576

*/