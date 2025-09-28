/*

Name: 1a.c
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

void handle_alarm(int sig){
    printf("ITIMER_REAL expired!: %d\n", sig);
}

int main(){
    struct itimerval timer;

    signal(SIGALRM, handle_alarm);  
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 10;
    
    if(setitimer(ITIMER_REAL, &timer, NULL) == -1){
        perror("setitimer");
        exit(1);
    }

    while(true) 
        pause(); 

    return 0;
}
