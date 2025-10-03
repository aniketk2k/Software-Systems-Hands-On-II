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
#include <unistd.h>

sem_t res;     // counting semaphore

void *job(void *arg){
    sem_wait(&res);   // grab a resource

    printf("Thread %lu got resource\n", pthread_self());
    sleep(1);         // pretend using it
    printf("Thread %lu released resource\n", pthread_self());

    sem_post(&res);   // give back
    return NULL;
}

int main(){
    pthread_t t[8];     // no of threads
    sem_init(&res, 0, 2);   // 2 fake resources

    for(int i=0; i<8; i++) 
        pthread_create(&t[i], NULL, job, NULL);
    for(int i=0; i<8; i++) 
        pthread_join(t[i], NULL);

    sem_destroy(&res);
    return 0;
}

/*

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/32$ gcc -o temp 32c.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/32$ ./temp
Thread 137005144995520 got resource
Thread 137005136602816 got resource
Thread 137005144995520 released resource
Thread 137005136602816 released resource
Thread 137005128210112 got resource
Thread 137005027555008 got resource
Thread 137005128210112 released resource
Thread 137005027555008 released resource
Thread 137005119817408 got resource
Thread 137005111424704 got resource
Thread 137005111424704 released resource
Thread 137005119817408 released resource
Thread 137005019162304 got resource
Thread 137005010769600 got resource
Thread 137005019162304 released resource
Thread 137005010769600 released resource

*/