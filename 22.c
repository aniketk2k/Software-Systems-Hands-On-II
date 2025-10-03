/*

Name: 22.c
Author: Aniket Kumar
Decsription: Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date: October 1st, 2025

*/


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/stat.h>

#define FIFO "myfifo"
#define BUF_SIZE 1024

int main() {
    char buf[BUF_SIZE];

    mkfifo(FIFO, 0666);
    int fd = open(FIFO, O_RDONLY | O_NONBLOCK);
    if(fd == -1){ 
        perror("open"); 
        return 1; 
    }

    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(fd, &fds);

    struct timeval tv = {10, 0};
    printf("Waiting for data on FIFO '%s' for 10 seconds...\n", FIFO);

    int ret = select(fd + 1, &fds, NULL, NULL, &tv);

    if(ret == -1) 
        perror("select");
    else if(ret == 0) 
        printf("Timeout: No data received.\n");
    else if(FD_ISSET(fd, &fds)){
        int n = read(fd, buf, BUF_SIZE - 1);
        if(n > 0){
            buf[n] = '\0'; 
            printf("Received: %s\n", buf); 
        }
        else if(n == 0) 
            printf("Writer closed FIFO.\n");
        else 
            perror("read");
    }

    close(fd);
    return 0;
}




/*
Try 1:
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc 22.c -o temp
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
Waiting for data on FIFO 'myfifo' for 10 seconds...
Timeout: No data received.


Try 2:
Terminal 1:
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc 22.c -o temp
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
Waiting for data on FIFO 'myfifo' for 10 seconds...
Received: Hello FIFO

Terminal 2:
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ echo "Hello FIFO" > myfifo

*/