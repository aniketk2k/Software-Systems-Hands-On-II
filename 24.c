/*

Name: 24.c
Author: Aniket Kumar
Decsription: Write a program to create a message queue and print the key and message queue id.
Date: September 28th, 2025

*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
    key_t key;
    int msgid;

    key = ftok("msgqueuefile", 65); 
    if(key == -1){
        perror("ftok");
        exit(1);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if(msgid == -1){
        perror("msgget");
        exit(1);
    }

    printf("Created message queue successfully!\n");
    printf("Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}

/*

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ touch msgqueuefile
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc 24.c -o temp
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
Created message queue successfully!
Key: 1090865187
Message Queue ID: 0

*/