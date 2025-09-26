/*

Name: 19.c
Author: Aniket Kumar
Decsription: Create a FIFO file by 
                a. mknod command 
                b. mkfifo command 
                c. use strace command to find out, which command (mknod or mkfifo) is better. 
                d. mknod system call 
                e. mkfifo library function
Date: September 26th, 2025

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(){
    const char *fifo_name = "myfifo_sys";
    // mode: 0666 (read/write for all), S_IFIFO for FIFO
    if(mknod(fifo_name, S_IFIFO | 0666, 0) == -1){
        perror("mknod");
        exit(1);
    }
    printf("FIFO %s created successflly using mknod system call\n", fifo_name);
    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/19$ gcc -o temp 19d.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/19$ ./temp
FIFO myfifo_sys created successfully using mknod system call

*/