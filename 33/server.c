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

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUF_SIZE] = {0};
    const char *message = "Hello from Server";

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Setup server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);

    // Accept connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Client connected\n");

    // Read message from client
    int valread = read(new_socket, buffer, BUF_SIZE);
    if (valread > 0) {
        printf("Client: %s\n", buffer);
    }

    // Send message to client
    send(new_socket, message, strlen(message), 0);
    printf("Message sent to client\n");

    // Close sockets
    close(new_socket);
    close(server_fd);

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