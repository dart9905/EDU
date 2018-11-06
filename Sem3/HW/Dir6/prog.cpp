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
    int size_str = 0;
    int num = 0;
    char str [MSG_SIZE];
    
    
    //printf("%i\n", sizeof (msgdata) - sizeof(long int));
    
    
    
    for (;strcmp(msgdata._data, "exit") != 0;) {
        
        
        printf(":");
        /*
        for (;scanf("%ld:%255[^\n]%*c", msgdata._type, msgdata._data) == 0; ) {};
        */
        scanf("%d", &num);
        scanf("%s",str);
        
        
        if (strcmp(str, "exit") != 0) {
            size_str = strlen(str);
            
            
            if (strcmp(str, "show") != 0 && size_str != 0) {
                
                
                msgdata._type = num;
                for (int i = 0; i < size_str; i++) {
                    msgdata._data [i] = str [i];
                }
                if (msgsnd (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 0) == -1) {
                    printf("HERNI POLNAI2\n");
                    return 0;
                }
                
            } else {
                
                if (msgrcv (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 1, 0) == -1) {
                    
                    printf("HERNI POLNAI2\n");
                    return 0;
                }
                
                
                //system("clear");
                printf("==========\n%s\n==========\n", msgdata._data);
                
            }
        }
        
    }
    
    return 0;
}
///Users/macbook/Documents/GitHub/EDU/Sem3/HW/Dir6/
