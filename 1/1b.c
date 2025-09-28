/*

Name: 1b.c
Author: Aniket Kumar
Decsription: Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second
                a. ITIMER_REAL
                b. ITIMER_VIRTUAL
                c. ITIMER_PROF
Date: September 28th, 2025

*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handle_vtalarm(int sig){
    printf("ITIMER_VIRTUAL expired!: %d\n", sig);
}

int main(){
    struct itimerval timer;

    signal(SIGVTALRM, handle_vtalarm);
    
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 10;

    if(setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1){
        perror("setitimer");
        exit(1);
    }

    while(true)

    return 0;
}
