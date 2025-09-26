/*

Name: 17.c
Author: Aniket Kumar
Decsription: Write a program to execute ls -l | wc.
                a. use dup
                b. use dup2
                c. use fcntl
Date: September 26th, 2025

*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2];
    pipe(fd);

    if(fork() == 0){  // child: ls -l
        close(fd[0]);
        int out = fcntl(fd[1], F_DUPFD, STDOUT_FILENO);
        if(out != STDOUT_FILENO){ 
            close(STDOUT_FILENO); 
            dup2(out, STDOUT_FILENO); 
            close(out); 
        }
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("ls"); exit(1);
    }

    // parent: wc
    close(fd[1]);
    int in = fcntl(fd[0], F_DUPFD, STDIN_FILENO);
    if(in != STDIN_FILENO){ 
        close(STDIN_FILENO);
        dup2(in, STDIN_FILENO); 
        close(in); 
    }
    close(fd[0]);
    execlp("wc", "wc", NULL);
    perror("wc"); exit(1);
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/17$ gcc -o temp 17c.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/17$ ./temp
      5      38     264

*/