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

void handle_sigint(int sig){
    printf("\nCaught SIGINT! Signal number: %d\n", sig);
    // exit(0); // optional: exit on Ctrl+C
}

int main() {
    signal(SIGINT, handle_sigint);

    printf("Press Ctrl+C to send SIGINT...\n");
    while(true) 
        sleep(1);

    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/8$ gcc -o temp 8b.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/8$ ./temp
Press Ctrl+C to send SIGINT...
^C
Caught SIGINT! Signal number: 2
^C
Caught SIGINT! Signal number: 2

*/