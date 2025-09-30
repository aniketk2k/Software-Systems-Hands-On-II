/*

Name: 7.c
Author: Aniket Kumar
Decsription: Write a simple program to print the created thread ids.
Date: September 30th, 2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Thread function
void* thread_func(void* arg){
    printf("Thread created with ID: %lu\n", pthread_self());
    return NULL;
}

int main(){
    pthread_t threads[3];
    
    for(int i=0; i<3; i++) 
        if(pthread_create(&threads[i], NULL, thread_func, NULL) != 0){
            perror("pthread_create");
            exit(1);
        }

    for(int i=0; i<3; i++) 
        pthread_join(threads[i], NULL);
    
    printf("Main thread exiting.\n");
    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc -o temp 7.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
Thread created with ID: 128386460546752
Thread created with ID: 128386452154048
Thread created with ID: 128386443761344
Main thread exiting.

*/