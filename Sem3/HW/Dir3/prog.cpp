#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int GLOBL_MAX_VAL = 21;
double GLOBL = 0.0;
double X = 0.0;
int N = 0.0;
double SING = 1.0;

const double Pi= 3.1415926536;


void* pthfun(void* num);

long double cos(long double x, int n);

long int factor(int n);

long double st (long double x, int n);

int cos_sing ();


int main () {
    X= 0.0;
    
    scanf("%lf", &X);
    
    cos_sing ();
    
    X = X * Pi / 180.0;
    
    pthread_t a [GLOBL_MAX_VAL];
    
    
    for (int i = 0; i < GLOBL_MAX_VAL; i++) {
        pthread_create(&(a [i]),(pthread_attr_t*)NULL, pthfun, NULL);
    }
    
    for (int i = 0; i < GLOBL_MAX_VAL; i++) {
        pthread_join(a [i], (void**)NULL);
    }
    
    GLOBL *= SING;
    
    
    
    printf("%g\n", GLOBL);
    
    return 0;
}



void* pthfun(void* num) {
    int n = N;
    N++;
    GLOBL += cos(X, n);
    return NULL;
}


long double cos(long double x, int n) {
    if (n < 0) {
        printf("Enter n greater than zero\n");
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
    long double cos_val = st(-1.0, n) * a / b;
    return cos_val;
}


long int factor(int n) {
    if (n == 0)
        return 1;
    long int fact = 0;
    for (fact = n; n > 1; n--, fact *= n) {}
    return fact;
}


long double st (long double x, int n) {
    
    long double xx = 1.0;
    
    if (x == 0.0 && n == 0) {
        return 1.0;
    }
    
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


int cos_sing () {
    if (X >= 360.0) {
        X = X - 360.0 * (int)(X / 360);
    }
    
    if (X >= 270.0) {
        X = 360.0 - X;
    }
    
    if (X >= 180.0) {
        X = X - 180.0;
        SING = -1.0;
    }
    
    if (X >= 90.0) {
        X = 180.0- X;
        SING = -1.0;
    }
    return 0;
}

///Users/macbook/Documents/GitHub/EDU/Sem3/HW/Dir3/
