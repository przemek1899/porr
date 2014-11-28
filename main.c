#include "matrixGenerator.h"
#include <stdio.h>
#include <time.h>

int main(){

    const double B_MAX_VALUE = 10.0*N;

    printf("projekt PORR\n");
    matrix A;
    getRichardsonMatrix(A);
    const double ALFA = getAlfa(A);
    int i,j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            printf("%f ", A[i][j]);
        }
        printf("\n");
    }

    zmp b[N];
    generateRandomVector(b, -B_MAX_VALUE, B_MAX_VALUE);

    zmp x[N];
    generateRandomVector(x, -1.0, 1.0);

    clock_t start_t, end_t, total_t;

    start_t = clock();

    int k=100; //liczba krokow
    for(i=0; i<k; i++){
        richardsonIteration(x, ALFA, A, b);
    }

    end_t = clock();
    total_t = (double) (start_t - end_t) / CLOCKS_PER_SEC;

    zmp y_test[N]; //do sprawdzenia wynikow
    multiplyMatrixVector(A, x, y_test);

    for(i=0; i<N; i++){
        printf("%f %f %f\n", b[i]-y_test[i], b[i], y_test[i]);
    }

    return 0;
}
