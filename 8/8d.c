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
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

void handle_sigalrm(int sig){
    printf("Caught SIGALRM! Signal number: %d\n", sig);
}

int main() {
    signal(SIGALRM, handle_sigalrm);

    printf("Alarm set for 5 seconds...\n");
    alarm(5);  // set alarm for 5 second

    while(true) 
        pause(); // wait for signal

    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/8$ gcc -o temp 8d.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/8$ ./temp
Alarm set for 5 seconds...
SCaught SIGALRM! Signal number: 14
^C

*/
