/*

Name: 11.c
Author: Aniket Kumar
Decsription: Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - use sigaction system call.
Date: September 28th, 2025

*/

#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

int main(){
    struct sigaction sa;

    sa.sa_handler = SIG_IGN;   // handler = ignore
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    printf("Ignoring SIGINT for 7 seconds. Pressing Ctrl+C wont terminate the program...\n");
    sleep(7);

    sa.sa_handler = SIG_DFL;   // handler = default action
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    printf("SIGINT is reset to default. Now Ctrl+C will work and terminate the program.\n");

    while(true) 
        sleep(1);

    return 0;
}



/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc -o temp 11.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
Ignoring SIGINT for 7 seconds. Pressing Ctrl+C wont terminate the program...
^C^C
^C
^C
^C
^C^C^C^C^C
SIGINT is reset to default. Now Ctrl+C will work and terminate the program.
^C

*/