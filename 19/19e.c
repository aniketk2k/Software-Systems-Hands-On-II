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
#include <sys/stat.h>
#include <stdlib.h>

int main(){
    const char *fifo_name = "myfifo_lib";
    if(mkfifo(fifo_name, 0666) == -1){
        perror("mkfifo");
        exit(1);
    }
    printf("FIFO %s created sccessfully using mkfifo library function\n", fifo_name);
    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/19$ gcc -o temp 19e.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/19$ ./temp
FIFO myfifo_lib created sccessfully using mkfifo library function

*/