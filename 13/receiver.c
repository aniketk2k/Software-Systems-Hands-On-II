/*

Name: 13.c
Author: Aniket Kumar
Decsription: Write two programs: first program is waiting to catch SIGSTOP signal, the second program will send the signal (using kill system call). 
                Find out whether the first program is able to catch the signal or not.
Date: September 28th, 2025

*/

#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

int main() {
    printf("PID: %d\n", getpid());
    while(true){ 
        printf("Running...\n"); 
        sleep(2); 
    }
    return 0;
}

/*
Terminal 1:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/13$ gcc receiver.c -o t2
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/13$ gcc sender.c -o t1
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/13$ ./t2
PID: 9652
Running...
Running...
Running...
Running...
Running...
Running...
Running...
Running...
Running...
Running...
Running...
Running...
Running...
Running...
Running...

[1]+  Stopped                 ./t2

*/