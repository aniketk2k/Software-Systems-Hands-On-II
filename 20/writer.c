/*

Name: 20.c
Author: Aniket Kumar
Decsription: Write a programs so that both can communicate by FIFO - Use one way communicaion
Date: September 27th, 2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){
    int fd;
    char message[] = "Hello from Writer!";

    // Open FIFO for writing
    fd = open("myfifo", O_WRONLY);
    if(fd == -1){
        perror("open");
        exit(1);
    }

    printf("Writer is sending message: %s\n", message);
    write(fd, message, strlen(message)+1); 
    close(fd);

    return 0;
}

/*
Terminal 2:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/20$ gcc writer.c -o temp2
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/20$ ./temp2
Writer is sending message: Hello from Writer!

*/