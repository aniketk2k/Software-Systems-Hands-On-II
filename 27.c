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
    key_t key = ftok("msgqprog", 65);
    if(key == -1){
        perror("ftok");
        exit(1);
    }

    int msgid = msgget(key, 0666 | IPC_CREAT);
    if(msgid == -1){
        perror("msgget");
        exit(1);
    }

    struct msgbuf msg;
    msg.type = 1;

    // a. Blocking receive (flag = 0)
    printf("Receiving message (blocking)...\n");
    if (msgrcv(msgid, &msg, sizeof(msg.text), msg.type, 0) == -1) {
        perror("msgrcv (blocking)");
    } else {
        printf("Received (blocking): %s\n", msg.text);
    }

    // b. Non-blocking receive (IPC_NOWAIT)
    printf("\nReceiving message (non-blocking)...\n");
    int ret = msgrcv(msgid, &msg, sizeof(msg.text), msg.type, IPC_NOWAIT);
    if(ret == -1){
        if(errno == ENOMSG) 
            printf("No message available (non-blocking)\n");
        else 
            perror("msgrcv (non-blocking)");
    } 
    else 
        printf("Received (non-blocking): %s\n", msg.text);

    return 0;
}
