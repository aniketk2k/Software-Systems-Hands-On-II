/*

Name: 8.c
Author: Aniket Kumar
Decsription: Write a separate program using signal system call to catch the following signals.
                a. SIGSEGV
                b. SIGINT
                c. SIGFPE
                d. SIGALRM (use alarm system call)
                e. SIGALRM (use setitimer system call)
                f. SIGVTALRM (use setitimer system call)
                g. SIGPROF (use setitimer system call)
Date: September 28th, 2025

*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handle_sigsegv(int sig){
    printf("Caught SIGSEGV! Signal number: %d\n", sig);
    exit(1);
}

int main(){
    signal(SIGSEGV, handle_sigsegv);

    // Cause segmentation fault
    int *ptr = NULL;
    *ptr = 42;  // triggers SIGSEGV

    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/8$ gcc -o temp 8a.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/8$ ./temp
Caught SIGSEGV! Signal number: 11

*/