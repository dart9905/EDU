#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long double GLOBL = 0.0;
long double X = 0.0;
long double N = 0.0;


void* pthfun(void* num);

long double cos(long double x, int n);

long double factor(int n);

long double st (long double x, int n);


int main () {
    
    printf("%ld\n", pthread_self());
    
    
    
    pthread_t a [2] = {0};
    
    pthread_create(a,(pthread_attr_t*)NULL, pthfun, NULL);
    
    pthread_join(a [0], (void**)NULL);
    
    
    printf("%ld\n", GLOBL);
    return 0;
}


void* pthfun(void* num) {
    printf("p1 %ld\n", pthread_self());
    GLOBL += cos(X, N);
    return NULL;
}


long double cos(long double x, int n) {
    if (n < 0 || x == 0.0) {
        printf("Enter n or x greater than zero\n");
        abort ();
    }
    long double a = st( x, 2 * n);
    if (a < 0.0) {
        return 0.0;
    }
    long double b = factor(2 * n);
    if (b < 0.0) {
        return 0.0;
    }
    return st(-1.0, n) * a / b;
}


long double factor(int n) {
    long double fact = 0;
    for (fact = n; n > 1; n--, fact *= n) {}
    return fact;
}


long double st (long double x, int n) {
    
    long double xx = 1.0;
    
    if (x == 0.0) {
        return 0.0;
    }
    
    if (x == 1.0) {
        return 1.0;
    }
    
    if (x == -1.0) {
        if (n % 2 == 0)
            return 1.0;
        else
            return -1.0;
    }
    for (; n > 0; n--, xx *= x) {
    }
    return xx;
}

///Users/macbook/Documents/GitHub/EDU/Sem3/Dir5/
