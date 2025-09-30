/*

Name: 31a.c
Author: Aniket Kumar
Decsription: Write a program to create a semaphore and initialize value to the semaphore.
                a. create a binary semaphore
                b. create a counting semaphore
Date: September 30th, 2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    key_t key = ftok("binsemfile", 65);
    if(key == -1){ 
        perror("ftok"); 
        exit(1); 
    }

    int semid = semget(key, 1, IPC_CREAT | 0666); // single semaphore
    if(semid == -1){ 
        perror("semget"); 
        exit(1); 
    }

    union semun{
        int val;
    } sem_attr;

    sem_attr.val = 1; 
    if(semctl(semid, 0, SETVAL, sem_attr) == -1){
        perror("semctl");
        exit(1);
    }

    printf("Binary semaphore created. ID: %d, Initial value: %d\n", semid, sem_attr.val);
    return 0;
}

/*

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/31$ touch binsemfile
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/31$ gcc 31a.c -o temp
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/31$ ./temp
Binary semaphore created. ID: 0, Initial value: 1

*/
