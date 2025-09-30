/*

Name: 30.c
Author: Aniket Kumar
Decsription: Write a program to create a shared memory.
                a. write some data to the shared memory
                b. attach with O_RDONLY and check whether you are able to overwrite.
                c. detach the shared memory
                d. remove the shared memory
Date: September 30th, 2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main(){
    key_t key = ftok("msgqprog", 65);
    if(key == -1){ 
        perror("ftok"); 
        exit(1); 
    }

    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if(shmid == -1){ 
        perror("shmget");
        exit(1); 
    }

    printf("Shared memory ID: %d\n", shmid);
    
    char *ptr = (char *)shmat(shmid, NULL, 0);
    if(ptr == (char *)-1){ 
        perror("shmat"); 
        exit(1); 
    }
    
    strcpy(ptr, "Hi, shared memory!");
    printf("Written: %s\n", ptr);
    shmdt(ptr);

    // Attach read-only and read data
    ptr = (char *)shmat(shmid, NULL, SHM_RDONLY);
    if(ptr == (char *)-1){ 
        perror("shmat readonly"); 
        exit(1); 
    }
    printf("Read-only: %s\n", ptr);
    shmdt(ptr);

    // d. Remove shared memory
    shmctl(shmid, IPC_RMID, NULL);
    printf("Shared memory removed.\n");

    return 0;
}

/*

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc 30.c -o temp
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
Shared memory ID: 6
Written: Hi, shared memory!
Read-only: Hi, shared memory!
Shared memory removed.

*/