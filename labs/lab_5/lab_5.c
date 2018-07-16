#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <papi.h>

#define MX 1024
#define NITER 10
#define MEGA 1000000
#define TOT_FLOPS (2*MX*MX*NITER)

double** allocateMat(int sz);
void assignMat(double** mat, int sz);
double** matMult(double** a, double** b, int sz);
void freeMat(void** mat, int sz);
void printMat(double** mat, int sz);
float gettime();

long_long t0, t1;	//papi
double endtime,starttime; // papi
long_long values[2]; // papi
int events[2] = {PAPI_L1_DCM, PAPI_FP_OPS};

/* Get actual CPU time in seconds */
float gettime() {
  return (float)(PAPI_get_virt_usec() * 1000000.0);
}

int main(int argv, char* argc[]) {
    // size of matrix sz x sz
    int sz = 25;

    // allocating multiplying matrix
    double** mat = allocateMat(sz);
    assignMat(mat, sz);

    if (PAPI_num_counters() < 2) { // papi
	    printf("No PAPI counters or PAPI not supported\n");
	    exit (EXIT_FAILURE);
	}
    t0 = gettime();

    // multiplying matrices and assigning result
    double** r = matMult(mat, mat, sz);

    t1 = gettime();

    printf("Time taken for multiplication: ");
    printf("%llu%n", t1 -t0);

    printf("Total software flops = %f\n", (float)TOT_FLOPS);
	printf("Total hardware flops = %lld\n", values[1]);
	printf("MFlop/s = %f\n", (float)(TOT_FLOPS/MEGA)/(t1-t0));
	printf("L2 data cache misses is %lld\n", values[0]);

    freeMat((void**)mat, sz);
    freeMat((void**)r, sz);
    return 0;
}

double** allocateMat(int sz) {
    double** mat;
    mat = (double**)  malloc(sz*sizeof(*mat));
    int i;
    for(i = 0; i < sz; i++) {
        mat[i]= (double*) malloc(sz * sizeof(*mat[i]));
    }
    return (mat);
}

void assignMat(double** mat, int sz) {
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++){
            mat[i][j] = 2.0;
        }
    }
}

double** matMult(double** a, double** b, int sz) {
    double** r = allocateMat(sz);
    int i, j, k;

    for (i = 0; i < sz; i++) {
        for (j = 0; j < sz; j++) {
            r[i][j] = 0;
            for (k = 0; k < sz; k++) {
                r[i][j] = ((a[i][k])*(b[k][j]));
            }
        }
    }

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

