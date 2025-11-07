/*

Name: 10a.c
Author: Aniket Kumar
Decsription: Write a seperate program using sigacton system call to catch the following signals.
                a. SIGSEGV
                b. SIGINT
                c. SIGFPE
Date: October 1st, 2025

*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig){
    printf("\nCaught SIGINT! Signal number: %d\n", sig);
}

int main(){
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    printf("Press Ctrl+C to trigger SIGINT...\n");
    while(true) 
        sleep(1);

    return 0;
}