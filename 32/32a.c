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

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define LIMIT 3    // how many tickets each thread issues

int cnt = 1;       // shared ticket counter
sem_t lock;        // using semaphore as lock

void *work(void *arg){
    for(int i=0; i<LIMIT; i++){
        sem_wait(&lock);               // lock
        printf("Thread %lu got ticket %d\n", pthread_self(), cnt++);
        sem_post(&lock);               // release lock
    }
    return NULL;
}

int main(){
    pthread_t t[3];     //thread array
    sem_init(&lock, 0, 1);   // binary semaphore

    for(int i=0; i<3; i++)
        pthread_create(&t[i], NULL, work, NULL);
    for(int i=0; i<3; i++) 
        pthread_join(t[i], NULL);

    sem_destroy(&lock);
    return 0;
}

/*

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/32$ gcc -o temp 32a.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/32$ ./temp
Thread 128313620166336 got ticket 1
Thread 128313620166336 got ticket 2
Thread 128313620166336 got ticket 3
Thread 128313603380928 got ticket 4
Thread 128313603380928 got ticket 5
Thread 128313603380928 got ticket 6
Thread 128313611773632 got ticket 7
Thread 128313611773632 got ticket 8
Thread 128313611773632 got ticket 9

*/