//
//  main.cpp
//  N
//
//  Created by macbook on 08.05.2020.
//  Copyright © 2020 macbook. All rights reserved.
//
//cmod +x build.sh
//./build.sh
//
//

#include <stdio.h>
#include <mpi.h>
#include <cstdlib>


int main (int argc, char *argv[])
{
    MPI_Init (&argc, &argv);
    
    double time0 = MPI_Wtime();
    double time4 = 0.0;
    
    // exp(x)
    int size = 0, rank = 0;
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    //argument error
    if (argc < 2) {
        printf("\n\nerror: not enough arguments. enter N.\n\n");
        MPI_Finalize();
        return 1;
    }
    
    int N = (int)atol(argv[1]);
    
    //the number must be greater than 0
    if (N < 1) {
        printf("\n\nerror: N < 1.\n\n");
        MPI_Finalize();
        return 2;
    }
    
    //checking if the final number is less than the number of processes
    
    if (size > N)
        size = N;
    
    // a set of numbers for summation
    int set = N / size;
    
     MPI_Status status; //for MPI_Recv
    
    double SUMpart = 0.0,
    var = 1.0,
    x = 0;
    
    
    switch (rank) {
        case 0: // MAIN BOSS
            
            /*
            
            printf("Calculate exp(x), enter x please.\nThe number \"x\" must be for example 2; -3; -0.6!\n");
            scanf("%lg", &x);
            printf("Thanks. exp(%lg) is being calculated\n", x);
             
            //*/
            
            x = 1;
            
            //give each process its the first number in the series, in my opinion it is the best way of counting.
            for (int i = 1, j = 0; i < N + 1; i++) {
                
                if ((i > set * j) && (i < size * set + 1)) {
                    MPI_Send(&var, 1, MPI_DOUBLE, j, 10, MPI_COMM_WORLD);
                    j++;
                    
                }
                //
                // var = (x^i)/(i!)
                //
                var *= (x / i);
                
                //check if the final number is not completely divided into processes
                if (i > size * set) {
                    SUMpart += var;
                }
                
            }
            
            
            
            
            break;
            
        default:
            
            break;
    }
    
    if (rank < size) {
        //each process gets the number x itself and the first member of the contract that is already subscribed
        MPI_Recv(&var, 1, MPI_DOUBLE, 0, 10, MPI_COMM_WORLD, &status);
    }
    MPI_Bcast(&x, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    //printf("rank = %i, x = %lg, var = %lg\n", rank, x, var);
    
    for (int i = rank * set + 1; i < (rank + 1) * set + 1; i++) {
        //printf("(%lg^%i)/(%i!) = %lg\n",x,i - 1,i - 1, var);
        SUMpart += var;
        var *= (x / i);
    }
    
    if (rank >= size) {
        SUMpart = 0.0;
    }
    
    double SUM = 0.0;
    MPI_Reduce(&SUMpart, &SUM, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    switch (rank) {
        case 0:
            printf("exp(%lg) = %lg\n",x, SUM);
            break;
            
        default:
            break;
    }
    
    
    
    time4 = MPI_Wtime();
    
    printf("rank = %i; runtime = %lg\n\n", rank, time4 - time0);
    
    MPI_Finalize();
    return 0;

}
