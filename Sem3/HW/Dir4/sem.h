#include <sys/sem.h>

int P(int ID, sembuf& sem) {
    sem.sem_num = 0;
    sem.sem_op = -1;
    sem.sem_flg =0;
    
    if (semop (ID, &sem, 1) == -1) {
        printf("error P\n");
        return -1;
    };
    return 0;
}

int V(int ID, sembuf& sem) {
    sem.sem_num = 0;
    sem.sem_op = 1;
    sem.sem_flg =0;
    
    
    if (semop (ID, &sem, 1) == -1) {
        printf("error V\n");
        return -1;
    };
    return 0;
}
