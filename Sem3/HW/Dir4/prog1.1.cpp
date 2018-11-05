#include <stdio.h>
#include <sys/ipc.h>
#include "sem.h"

int main () {
    
    key_t IDftok = ftok("Users/macbook/Documents/GitHub/EDU/Sem3/Dir/Dir6/text.txt",9);
    
    int IDsem = semget(IDftok, 1, 0666|IPC_CREAT|IPC_EXCL);
    
    sembuf sem;
    
    
    switch (IDsem) {
        case -1:
            IDsem = semget(IDftok, 1, 0666);
            
            switch (IDsem) {
                case -1:
                    printf("HERNI POLNAI\n");
                    return 0;
                    break;
                    
                default:
                    //последующие запуски
                    
                    V(IDsem, sem);
                    
                    break;
            }
            break;
            
        default:
            //первый запуск
            
            P(IDsem, sem);
            
            break;
    }
    
    
    return 0;
}
///Users/macbook/Documents/GitHub/EDU/Sem3/HW/Dir4/
