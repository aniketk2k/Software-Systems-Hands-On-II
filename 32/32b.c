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
#include <string.h>

char buf[100];
sem_t lock;

void *writer(void *arg) {
    sem_wait(&lock);   // enter critical section

    snprintf(buf, sizeof(buf), "Thread %lu wrote this", pthread_self());
    printf("%s\n", buf);

    sem_post(&lock);   // leave critical section
    return NULL;
}

int main() {
    pthread_t t[4];
    sem_init(&lock, 0, 1);

    for(int i=0; i<4; i++) 
        pthread_create(&t[i], NULL, writer, NULL);
    for(int i=0; i<4; i++) 
        pthread_join(t[i], NULL);

    sem_destroy(&lock);
    return 0;
}

/*

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/32$ gcc -o temp 32b.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/32$ ./temp
Thread 134696803497664 wrote this
Thread 134696795104960 wrote this
Thread 134696778319552 wrote this
Thread 134696786712256 wrote this

*/