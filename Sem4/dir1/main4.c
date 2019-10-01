#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int N = 1000000;

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    
    // Get the number of processes
    int size_t;
    MPI_Comm_size(MPI_COMM_WORLD, &size_t);
    
    // Get the rank of the process
    int size_r;
    MPI_Comm_rank(MPI_COMM_WORLD, &size_r);
    
    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int len_name;
    MPI_Get_processor_name(processor_name, &len_name);
    double pi_t = 0.0f;
    
    if(size_r != 0) {
        for(int i = size_r - 1; i < N; i += (size_t - 1)){
            pi_t += pow(-1, i) / (pow(3, i) * (2 * i + 1));
        }
        pi_t *= 2 * sqrt(3);
        
        printf("pi_t = %f;\n", pi_t);
        MPI_Send(&pi_t, sizeof(double) / 8, MPI_DOUBLE, 0, 33, MPI_COMM_WORLD);
        
    } else {
        double pi = 0.0f;
        for (int i = 1; i < size_t; i++){
            MPI_Recv(&pi_t, sizeof(double) / 8, MPI_DOUBLE, i, 33, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            pi += pi_t;
            
        }
        
        
        printf("pi = %f;\n", pi);
    }
    
    //Finalize the MPI environment.
    MPI_Finalize();
}
