#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>

/*

 clang -Wall -pedantic -o test prog1.1.cpp
 
 sudo ./test
сделать семафоры через сообщения
*/

struct msg_type {
    long int _type;
    char _data [10];
};

int main () {
    
    key_t IDftok = ftok("Users/macbook/Documents/GitHub/EDU/Sem3/Dir/Dir7/text.txt",19);
    
    int IDmsg = msgget(IDftok, 0666|IPC_CREAT);//|IPC_EXCL);
    
    
    msg_type msgdata = {1, "Hello\n"};
    
    if (IDmsg == -1) {
        printf("HERNI POLNAI1\n");
        return 0;
    }
    
    if (msgsnd (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 0) == -1) {
        
        printf("HERNI POLNAI2\n");
        return 0;
    }
    
    printf("%i\n", sizeof (msgdata) - sizeof(long int));
    /*
    
    if (msgrcv (IDmsg, &msgdata, sizeof(msgdata) - sizeof (msgdata._type), 1, 0) == -1) {
        
        printf("HERNI POLNAI2\n");
        return 0;
    }
    printf("%s", msgdata._data);
    */
    /*
    
    
    switch (IDmsg) {
        case -1:
            IDmsg = msgget(IDftok, 0666);
            
            switch (IDmsg) {
                case -1:
                    printf("HERNI POLNAI\n");
                    return 0;
                    break;
                    
                default:
                    //последующие запуски
                    
                    
                    break;
            }
            break;
            
        default:
            //первый запуск
            
            
            break;
    }
    */
    
    return 0;
}
///Users/macbook/Documents/GitHub/EDU/Sem3/Dir/Dir7
