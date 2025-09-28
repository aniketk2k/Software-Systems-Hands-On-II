/*

Name: 2.c
Author: Aniket Kumar
Decsription: Write a program to print the system resource limits. Use getrlimit system call.
Date: September 28th, 2025

*/

#include <stdio.h>
#include <sys/resource.h>

void show_limit(const char *name, int res){
    struct rlimit lim;
    if(getrlimit(res, &lim) == -1) 
        return;
    printf("%-20s Soft: %s  Hard: %s\n", name,
           (lim.rlim_cur == RLIM_INFINITY) ? "infinite" : (char [32]){0},
           (lim.rlim_max == RLIM_INFINITY) ? "infinite" : (char [32]){0});
    if(lim.rlim_cur != RLIM_INFINITY) 
        printf("\033[F%-20s Soft: %-10llu ", name, (unsigned long long)lim.rlim_cur);
    if(lim.rlim_max != RLIM_INFINITY) 
        printf("Hard: %-10llu\n", (unsigned long long)lim.rlim_max);
}

int main() {
    puts("System Resource Limits:");
    show_limit("CPU time", RLIMIT_CPU);
    show_limit("File size", RLIMIT_FSIZE);
    show_limit("Data seg", RLIMIT_DATA);
    show_limit("Stack size", RLIMIT_STACK);
    show_limit("Core file", RLIMIT_CORE);
    show_limit("Resident set", RLIMIT_RSS);
    show_limit("Processes", RLIMIT_NPROC);
    show_limit("Open files", RLIMIT_NOFILE);
    show_limit("Locked mem", RLIMIT_MEMLOCK);
    show_limit("Address space", RLIMIT_AS);
    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc -o temp 2.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
System Resource Limits:
CPU time             Soft: infinite  Hard: infinite
File size            Soft: infinite  Hard: infinite
Data seg             Soft: infinite  Hard: infinite
Stack size           Soft: 8388608    Core file            Soft:   Hard: infinitCore file            Soft: 0          Resident set         Soft: infinite  Hard: infinite
Processes            Soft: 62528      Hard: 62528     
Open files           Soft: 1024       Hard: 1048576   
Locked mem           Soft: 2070794240 Hard: 2070794240
Address space        Soft: infinite  Hard: infinite

*/