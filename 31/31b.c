/*

Name: 31b.c
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

int main(){
    key_t key = ftok("countsemfile", 65);
    if(key == -1){ 
        perror("ftok"); 
        exit(1); 
    }

    int semid = semget(key, 3, IPC_CREAT | 0666); // 3 semaphores in set
    if(semid == -1){ 
        perror("semget"); 
        exit(1); 
    }

    // See line 58 
    union semun{            
        unsigned short *array;
    } sem_attr;

    unsigned short arr[3] = {0, 1, 9}; // initial values
    sem_attr.array = arr;

    if(semctl(semid, 0, SETALL, sem_attr) == -1){
        perror("semctl");
        exit(1);
    }

    printf("Counting semaphore set created. ID: %d, Initial values: %d,%d,%d\n", semid, arr[0], arr[1], arr[2]);
    return 0;
}

/*

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/31$ touch countsemfile
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/31$ gcc 31b.c -o temp2
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/31$ ./temp2
Counting semaphore set created. ID: 1, Initial values: 0,1,9

*/



/*
union semun {
    int val;                  // Used for SETVAL
    struct semid_ds *buf;     // Used for IPC_STAT and IPC_SET
    unsigned short *array;    // Used for GETALL and SETALL
    struct seminfo *__buf;    // Used for IPC_INFO (Linux-specific)
};
*/