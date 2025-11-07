/*

Name: 25.c
Author: Aniket Kumar
Decsription: Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
                a. access permission
                b. uid, gid
                c. time of last message sent and received
                d. time of last change in the message queue
                e. size of the queue
                f. number of messages in the queue
                g. maximum number of bytes allowed
                h. pid of the msgsnd and msgrcv
Date: September 28th, 2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <time.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds info;

    // Ensure the file exists for ftok
    const char *filename = "msgqueuefile";
    FILE *f = fopen(filename, "a"); // create if doesn't exist, because ftok() requires files to generate key
    if(f) 
        fclose(f);

    key = ftok(filename, 65);
    if(key == -1){
        perror("ftok");
        exit(1);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if(msgid == -1){
        perror("msgget");
        exit(1);
    }

    if(msgctl(msgid, IPC_STAT, &info) == -1){
        perror("msgctl");
        exit(1);
    }

    printf("Message Queue Info:");
    printf("\na. Access permissions: %o", info.msg_perm.mode & 0777);
    printf("\nb. UID (owner) and GID (owner) are : %d and %d respectivly.", info.msg_perm.uid, info.msg_perm.gid);
    printf("\nc. Time of last message sent and received are: %s and %s respectively", ctime(&info.msg_stime), ctime(&info.msg_rtime));
    printf("\nd. Time of last change: %s", ctime(&info.msg_ctime));
    printf("\ne. Current size (in bytes) of queue: %ld", info.msg_cbytes);
    printf("\nf. Number of messages in queue: %ld", info.msg_qnum);
    printf("\ng. Maximum bytes allowed: %ld", info.msg_qbytes);
    printf("\nh. PID of last msgsnd and msgrcv are: %d & %d respectively.", info.msg_lspid, info.msg_lrpid);

    return 0;
}

/*

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc 25.c -o temp
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
Message Queue Info:
a. Access permissions: 666
b. UID (owner) and GID (owner) are : 1000 and 1000 respectivly.
c. Time of last message sent and received are: Thu Jan  1 05:30:00 1970
 and Thu Jan  1 05:30:00 1970
 respectively
d. Time of last change: Wed Oct 1 18:36:39 2025

e. Current size (in bytes) of queue: 0
f. Number of messages in queue: 0
g. Maximum bytes allowed: 16384
h. PID of last msgsnd and msgrcv are: 0 & 0 respectively.

*/