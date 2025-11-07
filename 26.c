/*

Name: 26.c
Author: Aniket Kumar
Decsription: Write a program to send messages to the message queue. Check $ipcs -q
Date: September 28th, 2025

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

// Define message structure
struct msg_buffer{
    long msg_type;     // must be > 0
    char msg_text[100];
};

int main() {
    key_t key;
    int msgID;
    struct msg_buffer message;

    key = ftok("msgqueuefile", 65);
    msgID = msgget(key, IPC_CREAT | 0666);

    message.msg_type = 1;
    printf("Enter message: ");
    fgets(message.msg_text, sizeof(message.msg_text), stdin);
    msgsnd(msgID, &message, strlen(message.msg_text)+1, 0);
    printf("Message sent successfully!\n");

    return 0;
}



/*

OUTPUT:

trafalgarlaw@ANIKETKUMAROMEN:~/Desktop/Software-Systems-Hands-On-II$ touch msgqueuefile
trafalgarlaw@ANIKETKUMAROMEN:~/Desktop/Software-Systems-Hands-On-II$ gcc -o temp 26.c
trafalgarlaw@ANIKETKUMAROMEN:~/Desktop/Software-Systems-Hands-On-II$ ./temp
Enter message: Hello there!  
Message sent successfully!
trafalgarlaw@ANIKETKUMAROMEN:~/Desktop/Software-Systems-Hands-On-II$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0xffffffff 0          trafalgarl 666        11           2           
0x41056929 1          trafalgarl 666        14           1   

*/
