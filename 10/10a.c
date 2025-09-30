#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigsegv(int sig){
    printf("Caught SIGSEGV! Signal number: %d\n", sig);
    exit(1);
}

int main(){
    struct sigaction sa;
    sa.sa_handler = handle_sigsegv;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGSEGV, &sa, NULL);

    // Cause segmentation fault
    int *ptr = NULL;
    *ptr = 42;

    return 0;
}
