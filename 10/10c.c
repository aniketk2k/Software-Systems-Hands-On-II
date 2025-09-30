#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handle_sigfpe(int sig){
    printf("Caught SIGFPE! Signal number: %d\n", sig);
    exit(1);
}

int main(){
    struct sigaction sa;
    sa.sa_handler = handle_sigfpe;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGFPE, &sa, NULL);

    int a = 5, b = 0;
    int c = a/b;  
    printf("Result: %d\n", c);

    return 0;
}
