#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/msg.h>

const int MSG_SIZE = 256;

struct _msg {
    int a_name;
    int b_name;
    char _data [MSG_SIZE];
};

class msg_type {
public:
    msg_type () {
        _type = 1;
        _data.a_name = 0;
        _data.b_name = 0;
    }
    
    msg_type (int IDmsg) {
        _type = 1;
        _data.a_name = 0;
        _data.b_name = 0;
        
        msgsnd (IDmsg, this, sizeof(*this) - sizeof (_type), 0);
        msgrcv (IDmsg, this, sizeof(*this) - sizeof (_type), 2, 0);
        
        
    }
    
    long int _type;
    _msg _data;
};

int main () {
    
    key_t IDftok = ftok("Users/macbook/Documents/GitHub/EDU/Sem3/Dir/Dir7/text.txt",19);
    
    int IDmsg = msgget(IDftok, 0666|IPC_CREAT);//|IPC_EXCL);
    if (IDmsg == -1) {
        printf("HERNI POLNAI1\n");
        return 0;
    }
    
    
    msg_type msgdata;
    msgdata._data.a_name = 4;
    
    int size_str = 0;
    int num = 0;
    char str [MSG_SIZE];
    
    
    
    for (;strcmp(str, "exit") != 0;) {
        
        
        printf(":");
        /*
         for (;scanf("%ld:%255[^\n]%*c", msgdata._type, msgdata._data) == 0; ) {};
         */
        scanf("%d", &num);
        scanf("%s",str);
        
        
        if (strcmp(str, "exit") != 0) {
            size_str = strlen(str);
            
            
            if (strcmp(str, "show") != 0 && size_str != 0) {
                
                msgdata._type = 1;
                msgdata._data.a_name = 4;
                msgdata._data.b_name = num;
                for (int i = 0; i < size_str; i++) {
                    msgdata._data._data [i] = str [i];
                }
                msgdata._data._data [size_str] = '\0';
                msgsnd (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 0);
                
                
            } else {
                
                msgrcv (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 4, 0);
                
                
                //system("clear");
                printf("==========\n%d -> %d\n%s\n==========\n",msgdata._data.a_name, msgdata._data.b_name, msgdata._data._data);
                msgdata._type = 1;
                msgdata._data.a_name = 3;
                
            }
        }
        str [0] = '\0';
        
    }
    
    return 0;
}
///Users/macbook/Documents/GitHub/EDU/Sem3/HW/Dir6/
