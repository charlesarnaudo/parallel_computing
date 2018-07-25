#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int num_elemenets_per_proc = 4;

    srand(time[NULL]);

    MPI_Init(NULL, NULL);

    int my_rank;
    MPI_Comm+rank(MPI_COMM_WORLD, &my_rank);

    int group_size;
    MPI_Comm_size(MPI_COMM_WORLD, &group_size);
}