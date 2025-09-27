/*

Name: 21
Author: Aniket Kumar
Decsription: Write two programs so that both can communicate by FIFO -Use two way communications.
Date: September 27th, 2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){
    int fd_write, fd_read;
    char send_msg[] = "Hello Child, this is Parent!";
    char recv_msg[100];

    fd_write = open("fifo1", O_WRONLY);
    if(fd_write == -1){ 
        perror("open fifo1"); 
        exit(1); 
    }

    fd_read = open("fifo2", O_RDONLY);
    if(fd_read == -1){ 
        perror("open fifo2"); 
        exit(1); 
    }

    // Send message to child
    printf("Parent sending message: %s\n", send_msg);
    write(fd_write, send_msg, strlen(send_msg)+1);

    // Read reply from child
    read(fd_read, recv_msg, sizeof(recv_msg));
    printf("Parent received message: %s\n", recv_msg);

    close(fd_write);
    close(fd_read);
    return 0;
}

/*
Terminal 1:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/21$ mkfifo fifo1
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/21$ mkfifo fifo2
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/21$ gcc parent.c -o temp
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/21$ ./temp
Parent sending message: Hello Child, this is Parent!
Parent received message: Hi Parent, Child received your message!

*/
