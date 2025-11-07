/*

Name: 27
Author: Aniket Kumar
Decsription: Write a program to receive messages from the message queue.
                a. with 0 as a flag
                b. with IPC_NOWAIT as a flag
Date: September 26th, 2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

#define MSG_SIZE 100

struct msgbuf{
    long type;
    char text[MSG_SIZE];
};

int main(){
    key_t key;
    int msgid;
    struct msgbuf msg;

    key = ftok("msgqueuefile", 65);
    if(key == -1){
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if(msgid == -1){
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Sending message
    msg.type = 1;
    strcpy(msg.text, "Hello from Aniket (testing)");

    if(msgsnd(msgid, &msg, strlen(msg.text) + 1, 0) == -1){
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    printf("Message sent successfully.\n");


    //a. Received message 
    printf("\nReceiving message (blocking mode)...\n");
    if(msgrcv(msgid, &msg, sizeof(msg.text), msg.type, 0) == -1)    //reads message but waits if no message
        perror("msgrcv (blocking)");
    else 
        printf("Received (blocking): %s\n", msg.text);

    
    //b. Trying to receive again (non-blocking mode)
    printf("\nReceiving message (non-blocking mode)...\n");
    int ret = msgrcv(msgid, &msg, sizeof(msg.text), msg.type, IPC_NOWAIT);  //reads message return instantly if no message
    
    if(ret == -1){
        if(errno == ENOMSG)
            printf("No message available (non-blocking)\n");
        else
            perror("msgrcv (non-blocking)");
    } 
    else 
        printf("Received (non-blocking): %s\n", msg.text);

        
    if(msgctl(msgid, IPC_RMID, NULL) == -1) 
        perror("msgctl (remove)");
    else 
        printf("\nMessage queue deleted successfully.\n");

    return 0;
}


/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Desktop/Software-Systems-Hands-On-II$ gcc -o temp 27.c
trafalgarlaw@ANIKETKUMAROMEN:~/Desktop/Software-Systems-Hands-On-II$ ./temp
Message sent successfully.

Receiving message (blocking mode)...
Received (blocking): Hello there!


Receiving message (non-blocking mode)...
Received (non-blocking): Hello from Aniket (testing)

Message queue deleted successfully.

*/
