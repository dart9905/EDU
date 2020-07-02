//
//  main.cpp
//  N
//
//  Created by macbook on 11.05.2020.
//  Copyright © 2020 macbook. All rights reserved.
//
//cmod +x build.sh
//./build.sh
//
//


/*
 
 Начально краевая задача с уравнением переноса:
 
    (du / dt) + 2 * (du / dx) = x + t
 
    u(x = 0) = exp(-t)
 
    u(t = 0) = cos(\pi * x)
 
 Введем сетку:
 
 x_n = n * h; n = 0,...,N; N * h = 1;
 t_j = j * \tau; j = 0,...,J; J * \tau = 1;
 
 Схема тогда:
 
    (y_n^{j + 1} - y_n^j) / \tau + 2 * (y_n^j - y_{n - 1}^j) / h = x_n + t_j
 
    y_0^j = exp (-t_j)
 
    y_n^0 = cos(\pi * x_n)
 
 устойчика при 2\tau <= h или J >= 2N
 порядок аппроксимации О(+h)
 
            |(n;j + 1)
            |
            |
            |
 ___________|(n;j)
 (n - 1;j)
 
 
 тогда:
 
 y_n^{j + 1} = y_n^j + \tau * (x_n + t_j) - 2 * \tau / h * (y_n^j - y_{n - 1}^j)
 
 */

#include <iostream>
#include <math.h>
#include <mpi.h>


const double pi = 3.1415926535;

const int N = 40;
const int J = 3 * N;

const double T = 1.0;
const double X = 1.0;
const double h = X / (double)N;
const double tau = T / (double)J;

//matrix access function, outputs the address of the desired cell j n
double* accessdata (double* data, int j, int n);

// solution function
// rank_set = rank*set
// j =[0;end)
// n =[0;end)
// data_old = pointer to the old layer
//            Warning: the layer may address an n-1 element!!!!!
// data_next = pointer to the new layer
// h and tau parameters of the grid step
int solution (int rank_set, int j, int n, double* data_old, double* data_next, double h, double tau);

#define PRINT_TIME(vol)\
vol

#define PRINT(vol)\
//vol

#define PRINTtoFILE(vol)\
//vol


int main (int argc, char *argv[])
{
    MPI_Init (&argc, &argv);
    
    int size = 0, rank = 0;
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    //
    // check: there must be at least N processors
    //
    if (size > N) {
        if (rank == 0) {
            printf("The number of processors must be at least N!\n\n\n");
        }
        MPI_Finalize();
        return 1;
    }

    double time = 0.0;
    double* data = NULL;        //master matrix
    double* data_next = NULL;   //new layer
    double* data_old = NULL;    //old layer
    double* data_swop = NULL;   //the address of the storage layers in the exchangeы
    
    if (rank == 0) {
        time = MPI_Wtime();
        data = (double *) calloc(N * J, sizeof(double));
        //to access the matrix
        //accessdata(data, N, j, n)
    }
    
    
    MPI_Status status; //for MPI_Recv
    
    int set = N / size; // the size of the set is processed by all processors
    
    
    data_old = (double *) calloc(set + 1, sizeof(double));
    data_next = (double *) calloc(set + 1, sizeof(double));
       
    for (int j = 0; j < J; j++) {
        
        //finding a solution for the layer assigned to the processor
        for (int n = 0; n < set; n++) {
            solution(rank * set, j, n, data_old + 1, data_next + 1, h, tau);
        }
        
        //sending the layer solution to the main processor
        MPI_Gather(data_next + 1, set, MPI_DOUBLE, data + j * N, set, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        
        switch (rank) {
            case 0:
                // finding a solution for layer cells that didn't end up in any of the processors due to the remainder of the N size partition
                for (int n = size * set; n < N; n++) {
                    solution(0, j, n, data + (j - 1) * N, data + j * N, h, tau);
                }
                
                //sending the edge solution to the next processor (n-1)
                if (size > 1) {
                    MPI_Send(data_next + set, 1, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
                }
                break;
            default:
                if (rank < size - 1) {
                    //sending the edge solution to the next processor (n-1)
                    MPI_Send(data_next + set, 1, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD);
                }
                //receiving an edge solution from the previous layer
                MPI_Recv(data_next, 1, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, &status);
                 
        }
        
        //layer swapping: now new layer has become old
        data_swop = data_old;
        data_old = data_next;
        data_next = data_swop;
        
    }
       
    PRINTtoFILE(
                FILE *files = NULL;
                )
    
    switch (rank) {
        case 0:
            
            time = MPI_Wtime() - time;
            
               
            //
            PRINT(
            for (int j = 0; j < J; j++) {
                for (int n = 0; n < N; n++) {
                
                    printf("%i %i %lg\n", j, n, *accessdata(data, j, n));
                }
            }
            )
            
            PRINT_TIME(
            printf("size = %i; rank = %i; runtime = %lg\n\n", size, rank, time);
            )
            
            
            PRINTtoFILE(
            files = fopen ("Print.txt", "wt");
            for (int j = 0; j < J; j++) {
                for (int n = 0; n < N; n++) {
                    
                    fprintf (files,"%lg ", *accessdata(data, j, n));
                }
                fprintf (files,"\n");
            }
            fclose(files);
            )
            
            free(data);
            break;
            
        default:
            break;
    }
    
    free(data_next);
    free(data_old);
    
   
    MPI_Finalize();
    return 0;

}




double* accessdata (double* data, int j, int n) {
    return (data + j * N + n);
}

int solution (int rank_set, int j, int n, double* data_old, double* data_next, double h, double tau) {
    
    
    if (j == 0) {
        data_next [n] = cos(pi * (n + rank_set) * h);
    }
    
    if (n + rank_set == 0) {
        data_next [n] = exp(-j * tau);
    }
    
    if (((n + rank_set) != 0) && (j != 0)) {
        data_next [n] = data_old [n] + tau * ((n + rank_set) * h + tau * (j - 1)) - 2 * tau / h * (data_old [n] -  data_old [n - 1]);
    }
    
    return 0;
}
