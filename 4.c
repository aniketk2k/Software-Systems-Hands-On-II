/*

Name: 4.c
Author: Aniket Kumar
Decsription: Write a program to measure how much time is taken to execute 100 getppid() system call. Use time stamp counter.
Date: September 28th, 2025

*/

#include <stdio.h>
#include <unistd.h>
#include <x86intrin.h>   

int main(){
    unsigned long long start, end;
    int i;

    getppid();
    start = __rdtsc();

    for(i=0; i<100; i++) 
        getppid();

    end = __rdtsc();
    unsigned long long cycles = end-start;
    unsigned long long avg_cyc = cycles/100;
    printf("Total cycles for 100 getppid() calls = %llu\n", cycles);
    printf("Average cycles per call = %llu\n", avg_cyc);

    return 0;
}

/*
OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ gcc -o temp 4.c
trafalgarlaw@ANIKETKUMAROMEN:~/Software System HandsOn II$ ./temp
Total cycles for 100 getppid() calls = 578448
Average cycles per call = 5784

*/