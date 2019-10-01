#include <stdio.h>
#include <mpi.h>

int 
main(int argc , char ** argv)
{
	MPI_Init(NULL , NULL);
	
	//Find out rank, size
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int number;
	if (world_rank == 0) {
		for(int i=1; i<world_size; ++i) {
			number = i;
			MPI_Send(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
	} else {
		MPI_Recv(&number, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD,
		MPI_STATUS_IGNORE);

		printf("Process %d received number %d from process 0\n", 
		world_rank , number);
	}


	MPI_Finalize();
	return 0;
}
                                         
