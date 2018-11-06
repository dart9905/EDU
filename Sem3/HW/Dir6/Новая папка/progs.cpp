#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/msg.h>

const int MSG_SIZE = 256;


struct msg_type {
    long int _type;
    char _data [MSG_SIZE];
};



int main () {
    
    key_t IDftok = ftok("Users/macbook/Documents/GitHub/EDU/Sem3/Dir/Dir7/text.txt",19);
    
    int IDmsg = msgget(IDftok, 0666|IPC_CREAT);//|IPC_EXCL);
    if (IDmsg == -1) {
        printf("HERNI POLNAI1\n");
        return 0;
    }
    
    msg_type msgdata;
    
    
    
    for (;;) {
        
        if (msgrcv (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 0, 0) == -1) {
            
            printf("HERNI POLNAI2\n");
            return 0;
        }
        system("clear");
        printf("==========\n%s\n==========\n", msgdata._data);
        if (msgsnd (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 0) == -1) {
            
            printf("HERNI POLNAI2\n");
            return 0;
        }
        
        
        
    }
    
    
    return 0;
}
///Users/macbook/Documents/GitHub/EDU/Sem3/HW/Dir6/
