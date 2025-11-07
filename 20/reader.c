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

int main(){
    int fd;
    char buffer[100];

    fd = open("myfifo", O_RDONLY);
    if(fd == -1){
        perror("open");
        exit(1);
    }

    read(fd, buffer, sizeof(buffer));
    printf("Reader: received message -> %s\n", buffer);
    close(fd);

    return 0;
}

/*
Terminal 1:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/20$ mkfifo myfifo
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/20$ gcc reader.c -o temp
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/20$ ./temp
Reader: received message -> Hello from Writer!

*/