//
//  main.cpp
//  N
//
//  Created by macbook on 18.11.2019.
//  Copyright © 2019 macbook. All rights reserved.
//


#include <stdio.h>
#include <mpi.h>


int main (int argc, char *argv[])
{
  int R, S;

  MPI_Init (&argc, &argv);
    
  MPI_Comm_rank (MPI_COMM_WORLD, &R);
  MPI_Comm_size (MPI_COMM_WORLD, &S);
    
  printf( "Hello N = %i; rang = %i\n\n", R, S);
    
  MPI_Finalize();
  return 0;
}
