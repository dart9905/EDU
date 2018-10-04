#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main () {
    
    int IDftok = ftok("Users/macbook/Documents/GitHub/EDU/Sem3/Dir4/text.txt",9);
    int IDshm = shmget(IDftok, sizeof(int)*3, 0666|IPC_CREAT|IPC_EXCL);
    
    int* array = NULL;
    
    switch (IDshm) {
        case -1:
            IDshm = shmget(IDftok, sizeof(int)*3, 0666);
            
            switch (IDshm) {
                case -1:
                    printf("HERNI POLNAI\n");
                    return 0;
                    break;
                    
                default:
                    array = (int*) shmat(IDshm, NULL, 0);
                    array [0]++;
                    array [2]++;
                    break;
            }
            break;
            
        default:
            //первый запуск
            array = (int*) shmat(IDshm, NULL, 0);
            array [0] = 1;
            array [1] = 0;
            array [2] = 1;
            
            break;
    }
    printf("1: %i; 2: %i; 1&2: %i.\n", array [0], array [1], array [2]);
    
    shmdt(array);
    
    
    return 0;
}
///Users/macbook/Documents/GitHub/EDU/Sem3/Dir4
