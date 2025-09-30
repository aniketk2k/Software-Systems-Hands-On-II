/*

Name: 9.c
Author: Aniket Kumar
Decsription: Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - Use signal system call.
Date: September 30th, 2025

*/

#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

int main(){
    int choice;
    printf("Choose:\n");
    printf("1. Ignore SIGINT (Ctrl+C)\n");
    printf("2. Reset SIGINT to default\n");
    scanf("%d", &choice);

    if(choice == 1){
        printf("Ignoring SIGINT for 10 seconds...\n");
        signal(SIGINT, SIG_IGN);
        sleep(10);
        printf("Done. Program will exit normally.\n");
    } 
    else if(choice == 2){
        printf("Setting SIGINT to default action...\n");
        signal(SIGINT, SIG_DFL);
        while(true) 
            sleep(1); // Ctrl+C to terminate the program
    } 
    else
        printf("Invalid choice!\n");

    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc -o temp 9.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
Choose:
1. Ignore SIGINT (Ctrl+C)
2. Reset SIGINT to default
1
Ignoring SIGINT for 10 seconds...
^C
^C
^C
^C^C^C^C^C
^C
Done. Program will exit normally.
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ 
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
Choose:
1. Ignore SIGINT (Ctrl+C)
2. Reset SIGINT to default
2
Setting SIGINT to default action...
^C

*/