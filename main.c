#include "matrixGeneratorOMP.h"
#include <stdio.h>
#include <time.h>
#include <omp.h>

zmp A[N][N];
zmp helpA[N][N];
zmp MAX_ERROR = 0.000001*N;
const int NUMBER_OF_TESTS = 5;

int main(){

    omp_set_num_threads(2);
    int iterations[NUMBER_OF_TESTS];
    zmp errors[NUMBER_OF_TESTS];
    double iteration_times[NUMBER_OF_TESTS];

    const double B_MAX_VALUE = 10.0*N;
    zmp b[N], x[N], y[N];
    zmp error;

    double start_t, end_t;
    double total_t;

    int iteration;
    for(iteration=0; iteration<NUMBER_OF_TESTS; iteration++){
        int counter=0; //licznik iteracji

        getRichardsonMatrix(A, helpA);
        const double ALFA = getAlfa(A);
        generateRandomVector(b, -B_MAX_VALUE, B_MAX_VALUE);
        generateRandomVector(x, -1.0, 1.0);

        int i,j;

        start_t = omp_get_wtime();
        do{
            #pragma omp parallel for shared(A,x,b,y) private(i,j)
            for(i=0;i<N; i++){
                zmp suma = 0.0;
                for(j=0; j<N; j++){
                    suma += A[i][j] * x[j];
                }
                y[i] = x[i] - ALFA * (suma - b[i]); //w wersji z OMP możnaby było zapisywać wynik od razu do tablicy x gdyby była synchronizacja ale to wydłużyłoby czas wykonywania
            }
            for(i=0; i<N; i++)
                x[i] = y[i];
            error = getError(A, x, b);
            ++counter;
        }
        while(error > MAX_ERROR);

        end_t = omp_get_wtime();
        total_t = (end_t - start_t);

        iterations[iteration] = counter;
        errors[iteration] = error;
        iteration_times[iteration] = total_t;
    }

    int n;
    double mean_time = 0.0;
    zmp mean_error = 0.0;
    double mean_iterations = 0.0;

    for(n=0; n<NUMBER_OF_TESTS; n++){
        mean_time += iteration_times[n];
        mean_error += errors[n];
        mean_iterations += iterations[n];
    }
    mean_time /= (double) NUMBER_OF_TESTS; mean_error /= (zmp) NUMBER_OF_TESTS; mean_iterations /= (double) NUMBER_OF_TESTS;

    FILE * pFile;
    pFile = fopen("whileOMP_N_2000.txt", "w");
    fprintf(pFile, "sredni czas: %f srednia liczba it: %f sredni bladE: %f\n\n", mean_time, mean_iterations, mean_error);
    for(iteration=0; iteration<NUMBER_OF_TESTS; iteration++){
        fprintf(pFile, "%d czas: %f it: %d blad: %f\n", iteration, iteration_times[iteration], iterations[iteration], errors[iteration]);
    }
    fprintf(pFile, "maxERROR: %f N=%d", MAX_ERROR, N);
    fclose(pFile);

   // printf("\nczas wykonywania zadania %f\nliczba iteracji %d\nMAX_ERROR %f error %f\n", total_t, counter, MAX_ERROR, error);
    return 0;
}

