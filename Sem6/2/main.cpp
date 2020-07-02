//
//  main.cpp
//  N
//
//  Created by macbook on 18.11.2019.
//  Copyright © 2019 macbook. All rights reserved.
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
    
    //argument error
    if (argc < 2) {
        printf("\n\nerror: not enough arguments. enter N.\n\n");
        MPI_Finalize();
        return 1;
    }
    
    int N = (int)atol(argv[1]),
    size = 0,
    rank = 0;
    
    //the number must be greater than 0
    if (N < 1) {
        printf("\n\nerror: N < 1.\n\n");
        MPI_Finalize();
        return 2;
    }
    
    int SUM = 0;
    
    MPI_Status status; //for MPI_Recv
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    //checking if the final number is less than the number of processes
    
    if (size > N)
        size = N;
    
    int set = N / size, // a set of numbers for summation
    sum_set = 0; // sum of a set of numbers
    
    switch (rank) {
        case 0: // MAIN BOSS
            
            //check if the final number is not completely divided into processes
            if (N > set * size) {
                for (int i = set * size + 1; i < N + 1; i++) {
                    SUM += i;
                }
                
            }
            
            //  I sum the numbers from
            //  1
            //  to
            //  set + 1
            for (int i = 1; i < set + 1; i++) {
                SUM += i;
            }
            
            //calculating the total amount
            for(int i = 1; i < size; i++) {
                MPI_Recv(&sum_set, 1, MPI_UNSIGNED, i, 10, MPI_COMM_WORLD, &status);
                SUM += sum_set;
            }
            printf("The work was divided into %i processes by %i numbers\n\n", size, set);
            printf("total sum of %i numbers = %i\n\n", N, SUM);
            
            break;
            
        default:
            //  I sum the numbers from
            //  rank * set + 1
            //  to
            //  (rank + 1) * set + 1
            if (rank >= size) {
                break;
            }
            
            //the calculation of the amounts
            for (int i = rank * set + 1; i < (rank + 1) * set + 1; i++) {
                sum_set += i;
            }
            
            MPI_Send(&sum_set, 1, MPI_UNSIGNED, 0, 10, MPI_COMM_WORLD);
            break;
    }
    
    
    MPI_Finalize();
    return 0;

}
