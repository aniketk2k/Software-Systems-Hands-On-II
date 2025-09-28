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
#include <sys/time.h>
#include <unistd.h>

void handle_sigalrm(int sig){
    printf("Caught SIGALRM (setitimer)! Signal number: %d\n", sig);
}

int main(){
    signal(SIGALRM, handle_sigalrm);

    struct itimerval timer;
    timer.it_value.tv_sec = 2;      // initial expiration
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 2;   // periodic
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);

    while(true) 
        pause();
    
    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/8$ gcc -o temp 8e.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/8$ ./temp
Caught SIGALRM (setitimer)! Signal number: 14
Caught SIGALRM (setitimer)! Signal number: 14
Caught SIGALRM (setitimer)! Signal number: 14
^C

*/
