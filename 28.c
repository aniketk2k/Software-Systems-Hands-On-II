/*

Name: 28.c
Author: Aniket Kumar
Decsription: Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date: September 30th, 2025

*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    key_t key;
    int msgID;
    struct msqid_ds buf;
    const char *filename = "msgqprog";

    // Ensure the file exists for ftok
    FILE *f = fopen(filename, "a");
    if(f) 
        fclose(f);
    
    key = ftok(filename, 65);
    if(key == -1){
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    msgID = msgget(key, 0666 | IPC_CREAT);
    if(msgID == -1){
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    if(msgctl(msgID, IPC_STAT, &buf) == -1){
        perror("msgctl IPC_STAT");
        exit(EXIT_FAILURE);
    }

    printf("Old permissions: %o\n", buf.msg_perm.mode & 0777);

    if((buf.msg_perm.mode & 0777) == 0666)
        buf.msg_perm.mode = 0644;
    else
        buf.msg_perm.mode = 0666;

    // Applying new permissions
    if(msgctl(msgID, IPC_SET, &buf) == -1){
        perror("msgctl IPC_SET");
        exit(EXIT_FAILURE);
    }
    printf("New permissions: %o\n", buf.msg_perm.mode & 0777);

    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc -o temp 28.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
Old permissions: 666
New permissions: 644

*/