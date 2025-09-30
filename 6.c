/*

Name: 6.c
Author: Aniket Kumar
Decsription: Write a simple program to create three threads.
Date: September 30th, 2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Thread function
void* thread_func(void* arg){
    int id = *((int*)arg);
    printf("It's Thread %d having (Thread_ID: %lu)\n", id, pthread_self());
    return NULL;
}

int main() {
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};

    for(int i=0; i<3; i++) 
        if(pthread_create(&threads[i], NULL, thread_func, &ids[i]) != 0){
            perror("pthread_create");
            exit(1);
        }

    for(int i=0; i<3; i++) 
        pthread_join(threads[i], NULL); // making main thread to wait for it's 3 threads

    printf("All threads finished.\n");
    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc -o temp 6.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
It's Thread 1 having (Thread_ID: 127960508004032)
It's Thread 2 having (Thread_ID: 127960499611328)
It's Thread 3 having (Thread_ID: 127960491218624)
All threads finished.

*/