#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig){
    printf("\nCaught SIGINT! Signal number: %d\n", sig);
}

int main(){
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    printf("Press Ctrl+C to trigger SIGINT...\n");
    while(true) 
        sleep(1);

    return 0;
}