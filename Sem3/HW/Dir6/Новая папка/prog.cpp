#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/msg.h>

const int MSG_SIZE = 256;
const int NUM_MANAGER = 1;
const int NUM_START = 2;

struct _msg {
    int a_name;
    int b_name;
    char _data [MSG_SIZE];
};

class msg_type {
public:
    msg_type () {
        _type = NUM_MANAGER;
        _data.a_name = 0;
        _data.b_name = 0;
    }
    
    msg_type (int IDmsg, int* IDMSG) {
        _type = NUM_MANAGER;
        _data.a_name = 0;
        _data.b_name = 0;
        
        msgsnd (IDmsg, this, sizeof(*this) - sizeof (_type), 0);
        msgrcv (IDmsg, this, sizeof(*this) - sizeof (_type), NUM_START, 0);
        if (this->_data.a_name == NUM_MANAGER) {
            *IDMSG = this->_data.b_name;
        }
        
        
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
    
    int IDMSG = 0;
    msg_type msgdata (IDmsg, &IDMSG);
    
    
    
    
    for (;strcmp(msgdata._data._data, "exit") != 0;) {
        
        
        printf(":");
        
        
        for (;scanf("%d:%255[^\n]%*c", &msgdata._data.b_name, msgdata._data._data) == 0; ) {};
        
        if (strcmp(msgdata._data._data, "exit") != 0) {
            
            
            if (strcmp(msgdata._data._data, "show") != 0) {
                
                msgdata._type = NUM_MANAGER;
                msgdata._data.a_name = IDMSG;
                
                
                msgsnd (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 0);
                
                
            } else {
                msgrcv (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), IDMSG, 0);
                
                
                //system("clear");
                printf("==========\n%d -> %d\n%s\n==========\n",msgdata._data.a_name, msgdata._data.b_name, msgdata._data._data);
                
            }
        }
        
    }
    
    return 0;
}
///Users/macbook/Documents/GitHub/EDU/Sem3/HW/Dir6/
