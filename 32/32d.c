/*

Name: 32
Author: Aniket Kumar
Decsription: Write a program to implement semaphore to protect any critical section.
                a. rewrite the ticket number creation program using semaphore
                b. protect shared memory from concurrent write access
                c. protect multiple pseudo resources ( may be two) using counting semaphore
                d. remove the created semaphore
Date: Oct 1st, 2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(){
    key_t key = ftok("semfile", 75);
    int semid = semget(key, 1, 0666);
    if(semid == -1){ 
        perror("semget"); 
        exit(1); 
    }

    if(semctl(semid, 0, IPC_RMID) == -1){
        perror("semctl remove");
        exit(1);
    }

    printf("Semaphore with ID %d removed.\n", semid);
    return 0;
}

/*

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/32$ gcc -o temp 32d.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/32$ ./temp
Semaphore with ID 2 removed.

*/