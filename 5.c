/*

Name: 5.c
Author: Aniket Kumar
Decsription: Write a program to print the system limitation of
                a. maximum length of the arguments to the exec family of functions.
                b. maximum number of simultaneous process per user id.
                c. number of clock ticks (jiffy) per second.
                d. maximum number of open files
                e. size of a page
                f. total number of pages in the physical memory
                g. number of currently available pages in the physical memory.
Date: September 28th, 2025

*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(){
    long val;

    val = sysconf(_SC_ARG_MAX);
    if(val == -1)
        perror("sysconf(_SC_ARG_MAX)");
    else
        printf("a. Max length of arguments to exec*: %ld\n", val);

    val = sysconf(_SC_CHILD_MAX);
    if(val == -1)
        perror("sysconf(_SC_CHILD_MAX)");
    else
        printf("b. Max simultaneous processes per user ID: %ld\n", val);

    val = sysconf(_SC_CLK_TCK);
    if(val == -1)
        perror("sysconf(_SC_CLK_TCK)");
    else
        printf("c. Number of clock ticks (jiffy) per second: %ld\n", val);

    val = sysconf(_SC_OPEN_MAX);
    if(val == -1)
        perror("sysconf(_SC_OPEN_MAX)");
    else
        printf("d. Max number of open files: %ld\n", val);

    val = sysconf(_SC_PAGESIZE);
    if(val == -1)
        perror("sysconf(_SC_PAGESIZE)");
    else
        printf("e. Page size (in bytes): %ld\n", val);

    val = sysconf(_SC_PHYS_PAGES);
    if(val == -1)
        perror("sysconf(_SC_PHYS_PAGES)");
    else
        printf("f. Total number of pages in physical memory: %ld\n", val);

    val = sysconf(_SC_AVPHYS_PAGES);
    if(val == -1)
        perror("sysconf(_SC_AVPHYS_PAGES)");
    else
        printf("g. Total number of currently vailable pages in physical memory: %ld\n", val);

    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc -o temp 5.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
a. Max length of arguments to exec*: 2097152
b. Max simultaneous processes per user ID: 62528
c. Number of clock ticks (jiffy) per second: 100
d. Max number of open files: 1024
e. Page size (in bytes): 4096
f. Total number of pages in physical memory: 4044524
g. Total number of currently vailable pages in physical memory: 2464422

*/