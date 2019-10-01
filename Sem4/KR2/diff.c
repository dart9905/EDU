#include <stdio.h>
#include <stdlib.h>
//#include <omp.h>
/*
 Make:
 gcc diff.c -std=c99
 
 gcc diff.c -lm -fopenmp -std=c99
 ./a.out
*/
const int M = 1000;
const int N = 2000000;

double omp_get_wtime(void);

int
main(int argc , char ** argv) {
    
    
    double t1, t2;
    
    //t1 = omp_get_wtime();
    
    double data_tmp [M];
	double data     [M];
    
	double t = 1.0/N;
    double h = 1.0/M;
    double a = 1.0;
    double k = a * a * t / h / h;
    
    if (2 * k > 1) {
        printf("урод\n");
        return 0;
    }
    
    data_tmp [0] = 0;
    data_tmp [M - 1] = 0;
    for (int j = 1; j < M - 1; j++) {
        data_tmp [j] = 100;
    }
    data [0] = 0;
    data [M - 1] = 0;
    
    
    int k2 = 0;
    
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M - 1; j++) {
            
            data [j] =
            k * data_tmp [j + 1] + (1.0 - 2.0 * k) * data_tmp [j] + k * data_tmp [j - 1];
        }
        //*
        if (k2 < (i * 100 / N)) {
            k2 += 1;
            printf("%i%%\n",i * 100 / N );
        }
        //*/
        for (int j = 1; j < M - 1; j++) {
            data_tmp [j] = data [j];
        }
        
    }
    for (int j = 0; j < M; j++) {
        //printf("data [%i] = %f\n",j, data [j]);
        printf("%f\n",j, data [j]);
    }
    
    
    //t2 = omp_get_wtime();
    
    //printf("%e\n", t2-t1);

	return 0;
}
