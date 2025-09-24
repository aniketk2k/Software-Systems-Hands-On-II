/*

Name: 15.c
Author: Aniket Kumar
Decsription: Write a simple program to send some data from parent to the child process.
Date: September 24th, 2025

*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int fd[2];          
    pid_t pid;
    char write_msg[] = "Hello Child! It's your parent";
    char read_msg[100];

    if(pipe(fd) == -1){
        perror("pipe");
        exit(1);
    }

    pid = fork(); 

    if(pid < 0){
        perror("fork");
        exit(1);
    }
    if(pid > 0){
        // Parent process --> write to pipe
        close(fd[0]); 
        printf("Parent writing: %s\n", write_msg);
        write(fd[1], write_msg, strlen(write_msg)+1);
        close(fd[1]); 
    }  
    else{
        // Child process --> read from pipe
        close(fd[1]); 
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child read: %s\n", read_msg);
        close(fd[0]); 
    }

    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc -o temp 15.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
Parent writing: Hello Child! It's your parent
Child read: Hello Child! It's your parent

*/