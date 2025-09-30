/*

Name: 29.c
Author: Aniket Kumar
Decsription: Write a program to remove the message queue.
Date: September 30th, 2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
    key_t key;
    int msgid;
    const char *filename = "msgqueuefile";

    // File should exist
    FILE *f = fopen(filename, "a");
    if(f) 
        fclose(f);

    key = ftok(filename, 65);
    if(key == -1){
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    msgid = msgget(key, 0666);  // getting existing queue
    if(msgid == -1){
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    if(msgctl(msgid, IPC_RMID, NULL) == -1){    // now removing it
        perror("msgctl IPC_RMID");
        exit(EXIT_FAILURE);
    }

    printf("Message queue removed successfully!\n");
    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc 29.c -o temp
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
Message queue removed successfully!

*/