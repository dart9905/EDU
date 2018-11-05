#include <sys/shm.h>

struct sembuf {
    int sem_num;        /* semaphore # */
    short   sem_op;         /* semaphore operation */
    short   sem_flg;        /* operation flags */
};

int semget(key_t key, int nsems, int semflg);

int semop(int semid, struct sembuf *sops, size_t nsops);



int semget(key_t key, int nsems, int semflg) {
    if (nsems < 0) {
        return -1;
    }
    int val = shmget(key, nsems * sizeof(int), semflg);
    if (val == -1) {
        return -1;
    }
    int* S = (int*) shmat(val, NULL, 0);
    return val;
}



int semop(int semid, struct sembuf *sops, size_t nsops) {
    
    if (semid < 1) {
        return -1;
    }
    if (sops == NULL) {
        return -1;
    }
    if (nsops < 0) {
        return -1;
    }
    
    int* S = (int*) shmat(semid, NULL, 0);
    
    for (int i = 0; i < nsops; i++) {
        
        if ((sops->sem_num == i) || (nsops == 0)) {
            if (sops->sem_op == 0) {
                while (S [i] != 0) {
                }
            }
            
            if (sops->sem_op < 0) {
                if (S[i] < -sops->sem_op) {
                    while (S[i] < -sops->sem_op) {
                        //printf("%d<%d\n", S[i], sops->sem_op);
                    }
                } else {
                    S[i] += sops->sem_op;
                }
            }
            
            if (sops->sem_op > 0) {
                S [i] += sops->sem_op;
            }
        }
        
    }
    return 0;
}

