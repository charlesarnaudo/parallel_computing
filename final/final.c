#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int compare(const void *a, const void *b);
void mergeArrays(int * arr, int * neighborArr, int * temp, int size, int rank);
int computeNeighborRank(int phase, int rank, int size);
void assignArr(int *mat, int size);

int main(int argc, char ** argv) {
    int rank, nproc;
    MPI_Status status;
    clock_t start = clock();

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    int numElements = 2048 / size;
    int *arr = (int* ) malloc(sizeof(int) * numElements);
    int *tempArr = (int* ) malloc(sizeof(int) * numElements * 2);
    int *recvArr = (int* ) malloc(sizeof(int) * numElements);

    if (rank == 0) {
        int *fullArr = (int* ) malloc(sizeof(int) * N);
    }

    assignArr(arr, numElements);

    qsort(arr, numElements, sizeof(int), compare);

    for (int n = 0; n < nproc; n++) {
        MPI_Barrier(MPI_COMM_WORLD);
        int neighbor = computeNeighborRank(n, rank, nproc);

        if (neighbor >= 0 && neighbor < nproc) {
            MPI_Sendrecv(arr, numElements, MPI_INT, neighbor, n, recvArr, numElements, MPI_INT, neighbor, n, MPI_COMM_WORLD, &status);
            if (rank < neighbor) {
                mergeArrays(arr, recvArr, tempArr, numElements, 1);
            } else {
                mergeArrays(arr, recvArr, tempArr, numElements, 0);
            }
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(arr, numElements, MPI_INT, fullArr, numElements, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Finalize();

    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // print out time it took for root to get back
    if (rank == 0) {
        printf("%f", cpu_time_used);
    }
    printf("\n");
    return 0;
}

void assignArr(int *arr, int numElements) {
    srand(time(NULL));
    for (int i = 0; i < numElements; i++) {
        arr[i] = rand();
    }
}

int compare(const void *a, const void *b) {
    if (a < b) {
        return -1;
    } else if (a > b) {
        return 1;
    } else {
        return 0;
    }
}

void mergeArrays(int *arr, int *neighborArr, int *temp, int nproc, int rank) {
    for (int i = 0, j = 0, k = 0; i < nproc * 2; i++) {
        if (j < nproc && k < nproc) {
            if (arr[j] < neighborArr[k]) {
                temp[i] = arr[j];
                j++;
            } else {
                temp[i] = neighborArr[k];
                k++;
            }
        } else if (j < nproc) {
            temp[i] = arr[j];
            j++;
        } else {
            temp[i] = neighborArr[k];
            k++;
        }
    }

    if (rank == 1) {
        for (int i = 0; i < nproc; i++) {
            arr[i] = temp[i];
        }
    } else {
        for (int i = nproc, j = 0; j < nproc; i++, j++) {
            arr[j] = temp[i];
        }
    }
}

int computeNeighborRank(int phase, int rank, int nproc) {
    int neighbor;
    if (phase % 2 != 0) {
        if (rank % 2 != 0) {
            neighbor = rank + 1;
        } else {
            neighbor = rank - 1;
        }
    } else {
        if (rank % 2 != 0) {
            neighbor = rank - 1;
        } else {
            neighbor = rank + 1;
        }
    }
    if (neighbor < 0 || neighbor >= nproc) {
        neighbor--;
    }
    return neighbor;
}

