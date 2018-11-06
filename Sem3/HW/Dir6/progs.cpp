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
    
    long int _type;
    _msg _data;
};

class manager_type {
public:
    
    manager_type ();
    ~manager_type ();
    int add ();
    int sub (int num);
    
    
    int* _data;
    int _size;
    int _cap;
    int _num;
    
};


int start (msg_type& msgdata, manager_type& manager, int IDmsg);
int list (msg_type& msgdata, manager_type& manager, int IDmsg);
int city (msg_type& msgdata, manager_type& manager, int IDmsg);

int main () {
    
    key_t IDftok = ftok("Users/macbook/Documents/GitHub/EDU/Sem3/Dir/Dir7/text.txt",19);
    
    int IDmsg = msgget(IDftok, 0666|IPC_CREAT);//|IPC_EXCL);
    if (IDmsg == -1) {
        printf("HERNI POLNAI1\n");
        return 0;
    }
    
    msg_type msgdata;
    manager_type manager;
    
    
    for (;;) {
        
        msgrcv (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), NUM_MANAGER, 0);
        switch (msgdata._data.a_name) {
            case 0:
                
                start (msgdata, manager, IDmsg);
                break;
                
            default:
                switch (msgdata._data.b_name) {
                    case 0:
                        manager.sub(msgdata._data.a_name);
                        break;
                        
                    case NUM_MANAGER:
                        list (msgdata, manager, IDmsg);
                        break;
                        
                    default:
                        city (msgdata, manager, IDmsg);
                        break;
                }
                break;
        }
    }
    
    
    return 0;
}
///Users/macbook/Documents/GitHub/EDU/Sem3/HW/Dir6/





manager_type:: manager_type () {
    _num = 3;
    _size = 5;
    _cap = 0;
    _data = new int (_size);
}
manager_type:: ~manager_type () {
    _num = 0;
    _size = 0;
    _cap = 0;
    delete [] _data;
    _data = NULL;
}

int manager_type:: add () {
    if (_cap >= _size) {
        
        int* newdata = new int [_size * 2];
        for (int i = 0; i < _size; i++) {
            newdata [i] = _data [i];
        }
        delete [] _data;
        _data = newdata;
        _size *= 2;
        
    }
    _data [_cap] = _num;
    _num++;
    _cap++;
    return _num - 1;
}

int manager_type:: sub (int num) {
    for (int i = 0; i < _cap + 1; i++) {
        if (_data[i] == num) {
            _data[i] = _data[_cap];
            _data[_cap] = 0;
            _cap--;
        }
    }
    return 0;
}


int start (msg_type& msgdata, manager_type& manager, int IDmsg) {
    
    msgdata._type = NUM_START;
    msgdata._data.a_name = NUM_MANAGER;
    msgdata._data.b_name = manager.add();
    
    
    msgsnd (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 0);
    
    msgdata._type = msgdata._data.b_name;
    msgdata._data.a_name = NUM_MANAGER;
    msgdata._data.b_name = manager._cap;
    
    
    msgsnd (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 0);
    
    for (int i = 0; i < manager._cap; i++) {
        msgdata._data.b_name = manager._data [i];
        msgsnd (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 0);
    }
    
    return 0;
}



int list (msg_type& msgdata, manager_type& manager, int IDmsg) {
    
    msgdata._type = msgdata._data.a_name;
    msgdata._data.a_name = NUM_MANAGER;
    msgdata._data.b_name = manager._cap;
    
    
    msgsnd (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 0);
    
    for (int i = 0; i < manager._cap; i++) {
        msgdata._data.b_name = manager._data [i];
        msgsnd (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 0);
    }
    
    return 0;
}


int city (msg_type& msgdata, manager_type& manager, int IDmsg) {
    
    if (msgdata._data.b_name == msgdata._data.a_name) {
        
        for (int i = 0; i < manager._cap; i++) {
            
            msgdata._type = manager._data [i];
            msgdata._data.b_name = manager._data [i];
            msgsnd (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 0);
        }
    } else {
        msgdata._type = msgdata._data.b_name;
        
        msgsnd (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 0);
    }
    return 0;
}
