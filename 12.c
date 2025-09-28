/*

Name: 12.c
Author: Aniket Kumar
Decsription: Write a program to create an orphan process. Use kill system call to send SIGKILL signal to the parent process from the child process.
Date: September 28th, 2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(){
    pid_t pid = fork();

    if(pid < 0){
        perror("fork failed");
        exit(1);
    }
    else if(pid == 0){
        printf("Child process (PID = %d) running...\n", getpid());
        printf("Killing parent process (PID = %d)...\n", getppid());

        kill(getppid(), SIGKILL);   // Send SIGKILL to parent

        sleep(5);   //making child orphan
        printf("Child (PID = %d) is now orphan. New parent is init/systemd (PID = %d)\n", getpid(), getppid());
    }
    else{
        printf("Parent process (PID = %d) running...\n", getpid());
        // Sleep so parent lives for a while unless killed
        sleep(10);
        printf("Parent still alive (this line should not print if killed by child).\n");
    }

    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc -o temp 12.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
Parent process (PID = 4995) running...
Child process (PID = 4996) running...
Killing parent process (PID = 4995)...
Killed
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ Child (PID = 4996) is now orphan. New parent is init/systemd (PID = 2101)

*/

/*
Why my init/systemd is not 1?
In systemd-based systems (all modern Ubuntu, Fedora, Arch, etc.), orphaned processes are not always reparented directly to PID 1.
Instead, they are reparented to a special "subreaper" process created by systemd.
That subreaper is responsible for cleaning up (waiting on) orphans.
*/