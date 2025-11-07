/*

Name: 34
Author: Aniket Kumar
Decsription: Write a program to create a concurrent server.
                a. use fork
                b. use pthread_create
Date: September 28th, 2025

*/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

#define PORT 8080
#define BACKLOG 5
#define BUF_SIZE 1024

// avoid zombie process
void handle_sigchld(int signo) {
    (void)signo;
    while(waitpid(-1, NULL, WNOHANG) > 0);  // WNOHANG don't block if no child has exited
}

int main() {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);  // IPv4, TCP
    if(server_sock < 0){ 
        perror("socket"); 
        exit(1); 
    }

    int opt = 1;
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));   // allows port to reuse immediately after restart of server

    struct sockaddr_in server_addr = {AF_INET, htons(PORT), INADDR_ANY};    // htons(PORT): converts port to network byte order
    memset(&server_addr.sin_zero, 0, 8);

    bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));    
    listen(server_sock, BACKLOG);

    signal(SIGCHLD, handle_sigchld);

    printf("Server listening on port %d...\n", PORT);

    while(true){
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);
        int client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_len);
        if(client_sock < 0) continue;

        printf("Connected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port)); // converts client's IP and port in human readable format

        if(!fork()){
            close(server_sock);
            char buf[BUF_SIZE] = {0};
            int n = recv(client_sock, buf, BUF_SIZE-1, 0);  // server reads client's message
            if(n > 0){
                buf[n] = '\0';
                printf("Client: %s\n", buf);
                send(client_sock, "Hello from server!\n", 19, 0);
            }
            close(client_sock);
            exit(0);
        }
        close(client_sock);
    }

    return 0;
}

/*

Terminal 1:
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/33$ cd ..
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ cd 34
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/34$ gcc -o temp 34a.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/34$ ./temp
Server listening on port 8080...
Connected: 127.0.0.1:43424
Client: Hi its Shanks

Connected: 127.0.0.1:49362
Client: Hello Law this side



Terminal 2:
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/34$ nc localhost 8080
Hi its Shanks
Hello from server!



Terminal 3:
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II/34$ nc localhost 8080
Hello Law this side
Hello from server!

*/