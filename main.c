#include "matrixGenerator.h"
#include <stdio.h>
#include <time.h>

int main(){

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

    zmp* b;
    generateRandomVector(b);

    zmp* x;
    // i teraz co? zerować wektor x czy wypełniać go losowymi liczbami?

    int k=1000; //liczba krokow
    for(i=0; i<k; i++){
        richardsonIteration(x, ALFA, A, b);
    }

    clock_t start_t, end_t, total_t;

    start_t = clock();

    //tu jest miejsce na Twój kod

    end_t = clock();
    total_t = (double) (start_t - end_t) / CLOCKS_PER_SEC;

    return 0;
}
