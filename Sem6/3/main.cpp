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
    
    int size = 0, rank = 0;
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    
    MPI_Status status; //for MPI_Recv
    
    int N = size;
    
    
    int buf [N];
    for (int i = 0; i < N; i++) {
        buf [i] = 0;
    }
    
    switch (rank) {
        case 0:     //MAIN BOSS
            
            for (int i = 0; i < N; i++) {
                buf [i] = i;
            }
            
            printf("buf[0] = %i\n\n", buf[0]);
            
            //if there are more processes we send them
            if (size > 1) {
                 MPI_Send(buf, size, MPI_INT, 1, 0, MPI_COMM_WORLD);
                 MPI_Recv(buf, size, MPI_INT, size - 1, 0, MPI_COMM_WORLD, &status);
            }
            printf("\n");
            printf("end\n");
            
            break;
            
        default:    //worker
                
                //take
            MPI_Recv(buf, size, MPI_INT, rank - 1,  0, MPI_COMM_WORLD, &status);
                
                //print
            printf("buf[%i] = %i\n\n", rank, buf [rank]);
                
                //give
            if (rank + 1 == size) {
                rank = -1;
            }
            
            MPI_Send(buf, size, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            break;
    }
    
    
    MPI_Finalize();
    return 0;

}
