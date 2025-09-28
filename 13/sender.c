/*

Name: 13.c
Author: Aniket Kumar
Decsription: Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). 
                Find out whether the first program is able to catch the signal or not.
Date: September 28th, 2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if(argc != 2){ 
        fprintf(stderr, "Usage: %s <pid>\n", argv[0]); 
        return 1; 
    }
    kill(atoi(argv[1]), SIGSTOP);
    printf("SIGSTOP sent to %s\n", argv[1]);
    return 0;
}

/*
Terminal 2:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/13$ ./t1 9652
SIGSTOP sent to 9652
*/

