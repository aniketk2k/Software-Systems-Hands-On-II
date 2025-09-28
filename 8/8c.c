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

void handle_sigfpe(int sig){
    printf("Caught SIGFPE! Signal number: %d\n", sig);
    exit(1);
}

int main(){
    signal(SIGFPE, handle_sigfpe);

    int a = 5, b = 0;
    int c = a/b; 
    printf("Result: %d\n", c);

    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/8$ gcc -o temp 8c.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/8$ ./temp
Caught SIGFPE! Signal number: 8

*/