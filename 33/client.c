/*

Name: 33
Author: Aniket Kumar
Decsription: Write a program to communicate between two machines using socket.
Date: October 1st, 2025

*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    const char *message = "Hello from Client";

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }

    send(sock, message, strlen(message), 0);
    printf("Message sent to server\n");

    int valread = read(sock, buffer, 1024);
    if(valread > 0) 
        printf("Server: %s\n", buffer);
    
    close(sock);
    return 0;
}

/*

Terminal 1:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/33$ gcc client.c -o t1
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/33$ gcc server.c -o t2
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/33$ ./t2
Server listening on port 8080...
Client connected
Client: Hello from Client
Message sent to client

Terminal 2:
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/33$ ./t1
Message sent to server
Server: Hello from Server

*/