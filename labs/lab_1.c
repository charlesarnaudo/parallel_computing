#include <stdio.h>
#include <stdlib.h>

void assignMatrix(double** mat, double* vec, int n);
void printMatVec(double** mat, double* vec, double* res, int n);
double* mvpms(double** mat, double* vec, int n);
void freeMatrix(void **mat, int n);

int main(int argc, char *argv[]){

    double* vec;
    double** mat;
    int n=5;

    //allocate vector and matrix (can use sizeof(double)
    //or the sizeof(pointer) since the compiler knows the sizes of stuff)
    vec = (double*) malloc(n*sizeof(*vec));
    mat = (double**)  malloc(n*sizeof(*mat));
    for(int i=0;i<n;i++)
        mat[i]= (double*) malloc(n*sizeof(*mat[i]));

    assignMatrix(mat,vec,n);

    double* resms = mvpms(mat,vec,n);

    printMatVec(mat,vec,resms,n);

    freeMatrix((void**)mat,n);
    free(vec);
    free(resms);

    return 0;
}

double* mvpms(double** mat, double* vec, int n){
    double *resms = (double*) malloc(n*sizeof(*resms));
    double sum=0;

    for(int i=0;i<n;i++){
       sum=0;
        for(int j=0;j<n;j++){
            sum+=mat[i][j]*vec[j];
        }
        resms[i] = sum;
    }
    return resms;
}

void assignMatrix(double** mat, double* vec, int n){

    for(int i=0;i<n;i++){
        vec[i]=1;
        for(int j=0;j<n;j++){
            if(i==j) mat[i][j]=2;
            else if(j==i+1) mat[i][j]=1;
            else if(j==i-1) mat[i][j]=1;
            else mat[i][j]=0;
        }
    }
}

void printMatVec(double** mat, double* vec, double* res, int n){
    for (int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%5.2f ",mat[i][j]);
        }
        if(i==n/2) printf("  %5.2f  =  %5.2f \n",vec[i],res[i]);
        else printf("  %5.2f     %5.2f\n",vec[i],res[i]);
    }
}

void freeMatrix(void **mat,int n){
    for(int i=0;i<n;i++)
        free(mat[i]);
    free(mat);
}

   