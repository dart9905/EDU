#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

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
                    
                    
                    sem.sem_num = 0;
                    sem.sem_op = -1;
                    sem.sem_flg =0;
                    
                    if (semop (IDsem, &sem, 1) == -1) {
                        printf("error");
                    };
                    
                    break;
            }
            break;
            
        default:
            //первый запуск
            
            
            sem.sem_num = 0;
            sem.sem_op = 1;
            sem.sem_flg =0;
            
            
            if (semop (IDsem, &sem, 1) == -1) {
                printf("error");
            };
            
            
            sem.sem_op = 0;
            
            if (semop (IDsem, &sem, 1) == -1) {
                printf("error");
            };
            
            break;
    }
    
    
    return 0;
}
///Users/macbook/Documents/GitHub/EDU/Sem3/Dir/Dir6
