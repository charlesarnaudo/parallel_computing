#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double** allocateMat(int sz);
void assignMat(double** mat, int sz);
double** matMult(double** a, double** b, int sz);
void freeMat(void** mat, int sz);
void printMat(double** mat, int sz);

int main(int argv, char* argc[]) {
    // size of matrix sz x sz
    int sz = 5;
    
    // allocating multiplying matrix
    double** mat = allocateMat(sz);
    assignMat(mat, sz);

    // multiplying matrices and assigning result
    double** r = matMult(mat, mat, sz);

    // printMat(mat, sz);
    // printf("\n");

    // print result
    printMat(r, sz);

    // free memory
    freeMat((void**)mat, sz);
    freeMat((void**)r, sz);
}

double** allocateMat(int sz) {
    double** mat;
    mat = (double**)  malloc(sz*sizeof(*mat));
    int i;
    #pragma omp parallel for schedule(dynamic) private(i) shared(mat)
    for(i = 0; i < sz; i++) {
        mat[i]= (double*) malloc(sz * sizeof(*mat[i]));
    }
    return (mat);
}

void assignMat(double** mat, int sz) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++){
            mat[i][j] = 2.0;
        }
    }
}

double** matMult(double** a, double** b, int sz) {
    double start = omp_get_wtime();
    double** r = allocateMat(sz);
    int i, j, k;
    
    #pragma omp parallel for schedule(dynamic) private(i, j, k) shared(r)
    for (i = 0; i < sz; i++) {
        for (j = 0; j < sz; j++) {
            r[i][j] = 0;
            for (k = 0; k < sz; k++) {
                r[i][j] = ((a[i][k])*(b[k][j]));
            }
        }
    }

    double end = omp_get_wtime();
	printf("Mult time: %lf\n", end - start);
    return(r);
}

void printMat(double** mat, int sz) {
    for (int i = 0; i < sz; i++) {
        for(int j = 0; j < sz; j++)  {
            printf("%5.2f ", mat[i][j]);
        }
        printf("\n");
    }
}

void freeMat(void** mat, int sz) {
    for(int i = 0; i < sz; i++)
        free(mat[i]);
    free(mat);
}

