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

void handle_sigprof(int sig){
    printf("Caught SIGPROF! Signal number: %d\n", sig);
}

int main(){
    signal(SIGPROF, handle_sigprof);

    struct itimerval timer;
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 500000; // 0.5 sec
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 500000;

    setitimer(ITIMER_PROF, &timer, NULL);

    while(true) 
        for(volatile int i=0; i<1000000; i++); // consume CPU + system time

    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/8$ gcc -o temp 8g.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/8$ ./temp
Caught SIGPROF! Signal number: 27
Caught SIGPROF! Signal number: 27
Caught SIGPROF! Signal number: 27
Caught SIGPROF! Signal number: 27
^C

*/