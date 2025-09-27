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

int main() {
    int fd_read, fd_write;
    char recv_msg[100];
    char send_msg[] = "Hi Parent, Child received your message!";

    fd_read = open("fifo1", O_RDONLY);
    if(fd_read == -1){ 
        perror("open fifo1"); 
        exit(1); 
    }

    fd_write = open("fifo2", O_WRONLY);
    if(fd_write == -1){ 
        perror("open fifo2"); 
        exit(1); 
    }

    // Read message from parent
    read(fd_read, recv_msg, sizeof(recv_msg));
    printf("Child received message from parent: %s\n", recv_msg);

    // Send reply to parent
    printf("Child sending message to parent: %s\n", send_msg);
    write(fd_write, send_msg, strlen(send_msg)+1);

    close(fd_read);
    close(fd_write);
    return 0;
}

/*
Terminal 2:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/21$ gcc child.c -o temp2
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/21$ ./temp2
Child received message from parent: Hello Child, this is Parent!
Child sending message to parent: Hi Parent, Child received your message!

*/