/*

Name: 17.c
Author: Aniket Kumar
Decsription: Write a program to execute ls -l | wc.
                a. use dup
                b. use dup2
                c. use fcntl
Date: September 26th, 2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2];
    pid_t pid;

    if(pipe(fd) == -1){
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if(pid < 0){
        perror("fork");
        exit(1);
    }

    if(pid == 0){
        close(fd[1]); 
        dup2(fd[0], STDIN_FILENO); // redirect stdin
        close(fd[0]);
        execlp("wc", "wc", (char *)NULL);
        perror("execlp wc");
        exit(1);
    } 
    else{
        close(fd[0]); 
        dup2(fd[1], STDOUT_FILENO); // redirect stdout
        close(fd[1]);
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls");
        exit(1);
    }
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/17$ gcc -o temp 17b.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/17$ ./temp
      5      38     264
      
*/