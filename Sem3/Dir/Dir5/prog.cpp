#include <stdio.h>
#include <pthread.h>

int GLOBL = 0;


void* myfun1(void* num) {
    printf("p1 %ld\n", pthread_self());
    GLOBL++;
    return NULL;
}


int main () {
    printf("%ld\n", pthread_self());
    
    pthread_t a = 0;
    
    int st1 = pthread_create(&a,(pthread_attr_t*)NULL, myfun1, NULL);
    int st2 = pthread_create(&a,(pthread_attr_t*)NULL, myfun1, NULL);
    
    st1 = pthread_join(a, (void**)NULL);
    st2 = pthread_join(a, (void**)NULL);
    printf("%d\n", GLOBL);
    return 0;
}
///Users/macbook/Documents/GitHub/EDU/Sem3/Dir5/
