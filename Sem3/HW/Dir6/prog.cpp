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
    
    
    long int _type;
    _msg _data;
    
    msg_type () {
        _type = NUM_MANAGER;
        _data.a_name = 0;
        _data.b_name = 0;
    }
    msg_type (int IDmsg, int* iduse, int* User, int* User_size);
    int check_list (int iduse, int IDmsg, int* User_n, int* User_size);
};

int printf_online (int* User, int User_size, int iduse);

int show (int IDmsg, msg_type& msgdata, int iduse);

int drop (msg_type& msgdata, int iduse, int IDmsg);



int main () {
    
    key_t IDftok = ftok("Users/macbook/Documents/GitHub/EDU/Sem3/Dir/Dir7/text.txt",19);
    
    int IDmsg = msgget(IDftok, 0666|IPC_CREAT);//|IPC_EXCL);
    if (IDmsg == -1) {
        printf("HERNI POLNAI1\n");
        return 0;
    }
    
    int iduse = 0;
    int User [MSG_SIZE];
    int User_size = 0;
    msg_type msgdata (IDmsg, &iduse, User, &User_size);
    
    printf_online(User, User_size, iduse);
    
    
    for (;strcmp(msgdata._data._data, "exit") != 0;) {
        
        printf(":>");
        for (;scanf("%d %255[^\n]%*c", &msgdata._data.b_name, msgdata._data._data) == 0; ) {};
        
        if (strcmp(msgdata._data._data, "exit") != 0) {if (strcmp(msgdata._data._data, "show") != 0) {
                if (strcmp(msgdata._data._data, "list") != 0) {
                    
                        drop (msgdata, iduse, IDmsg);
                    
                } else {
                    
                        msgdata.check_list (iduse, IDmsg, User, &User_size);
                        printf_online(User, User_size, iduse);
                    
                }
            } else {
                
                        show(IDmsg, msgdata, iduse);
            }
        }
    }
    
    msgdata._type = NUM_MANAGER;
    msgdata._data.a_name = iduse;
    msgdata._data.b_name = 0;
    msgsnd (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 0);
    
    return 0;
}




msg_type:: msg_type (int IDmsg, int* iduse, int* User, int* User_size) {
    _type = NUM_MANAGER;
    _data.a_name = 0;
    _data.b_name = 0;
    
    msgsnd (IDmsg, this, sizeof(*this) - sizeof (_type), 0);
    msgrcv (IDmsg, this, sizeof(*this) - sizeof (_type), NUM_START, 0);
    if (_data.a_name == NUM_MANAGER) {
        *iduse = _data.b_name;
    }
    
    msgrcv (IDmsg, this, sizeof(*this) - sizeof (_type), *iduse, 0);
    *User_size = _data.b_name;
    
    for (int i = 0; i < *User_size; i++) {
        msgrcv (IDmsg, this, sizeof(*this) - sizeof (_type), *iduse, 0);
        User [i] = _data.b_name;
        
    }
}


int printf_online(int* User, int User_size, int iduse) {
    printf("online %d\n", User_size);
    for (int i = 0; i < User_size; i++) {
        printf("us %d\n", User [i]);
    }
    printf("you %d\n", iduse);
    return 0;
}


int show(int IDmsg, msg_type& msgdata, int iduse) {
    if (msgrcv (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), iduse, IPC_NOWAIT) != -1) {
        //system("clear");
        printf("==========\n%d -> %d\n%s\n==========\n",msgdata._data.a_name, msgdata._data.b_name, msgdata._data._data);
    }
    return 0;
}


int drop (msg_type& msgdata, int iduse, int IDmsg) {
    msgdata._type = NUM_MANAGER;
    msgdata._data.a_name = iduse;
    msgsnd (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 0);
    return 0;
}


int msg_type:: check_list (int iduse, int IDmsg, int* User_n, int* User_size) {
    
    _type = NUM_MANAGER;
    _data.a_name = iduse;
    _data.b_name = NUM_MANAGER;
    
    msgsnd (IDmsg, this, sizeof(*this) - sizeof (_type), 0);
    
    msgrcv (IDmsg, this, sizeof(*this) - sizeof (_type), iduse, 0);
    
    *User_size = _data.b_name;
    
    for (int i = 0; i < *User_size; i++) {
        msgrcv (IDmsg, this, sizeof(*this) - sizeof (_type), iduse, 0);
        User_n [i] = _data.b_name;
        
    }
    return 0;
}
///Users/macbook/Documents/GitHub/EDU/Sem3/HW/Dir6/
