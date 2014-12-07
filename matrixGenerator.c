#include <gsl/gsl_rng.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include <omp.h>
#include "matrixGeneratorOMP.h"

const double A_MAX_VALUE = 10.0;

zmp getAlfa(zmp m[N][N]){
    // find the largest element na przekątnej
    zmp max = DBL_MIN;
    int i,j;
    for(i=0; i<N; i++){
        if (max < m[i][i])
            max = m[i][i];
    }
    // ale alfa ma być mniejsze niż 1/max
    if (max + 10.0 < DBL_MAX)
        return 1.0/(max+10.0);
    return 1.0/max;
}

void generateRandomVector(zmp vector[N], zmp a, zmp b){
    gsl_rng * generator;
    generator = gsl_rng_alloc(gsl_rng_default);

    time_t t;
    gsl_rng_set (generator, (unsigned) time(&t) ); //ustawienie ziarna

    int x;
    for(x=0; x<N; x++){
        vector[x] = (b-a) * gsl_rng_uniform(generator) + a; //B_MAX_VALUE * ((2*gsl_rng_uniform(generator))-1);
    }

    gsl_rng_free(generator);
    return;
}

void getRichardsonMatrix(zmp m[N][N], zmp symmetric[N][N]){

    double start_t, end_t;
    double total_t;

    //generate random matrix
    time_t t;
    gsl_rng * generator;
    generator = gsl_rng_alloc(gsl_rng_default);
    gsl_rng_set (generator, (unsigned) time(&t)); //ustawienie ziarna

    int x,y;//x - wiersze, y - kolumny
    for(x=0; x<N; x++){
        for(y=0; y<N; y++){
            m[x][y] =  (2*gsl_rng_uniform(generator))-1;
        }
    }
    gsl_rng_free(generator);


    //get symmetric matrix
    int k;
    for(x=0; x<N; x++){
        for(y=0; y<N; y++){
            symmetric[x][y] = 0.0;
        }
    }
    /*
    omp_set_num_threads(2);

    start_t = omp_get_wtime();
    #pragma omp parallel for private(x,y,k)
    for(x=0; x<N; x++){
        for(y=0; y<N; y++){
            zmp suma = 0.0;
            for(k=0; k<N; k++)
                suma += m[x][k]*m[y][k];
            symmetric[x][y] = suma;
        }
    }
    end_t = omp_get_wtime();
    total_t = (end_t - start_t);
    printf("\nczas generowania macierzy symetrycznej %f\n", total_t);

    //przepisywanie do macierzy m
    for(x=0; x<N; x++){
        for(y=0; y<N; y++){
            m[x][y] = symmetric[x][y];
        }
    }*/

    omp_set_num_threads(2);

   // start_t = omp_get_wtime();
    #pragma omp parallel for private(x,y,k)
    //oszczedna wersja macierzy sym
    //elementy na głównej przekątnej możnaby było pominąć ale je mnożymy, ponieważ wtedy zadanie jest lepiej uwarunkowane numerycznie - dowiedzione empirycznie
    for(x=0; x<N; x++){
        for(y=0; y<x+1; y++){
            zmp suma = 0.0;
            for(k=0; k<N; k++)
                suma += m[x][k]*m[y][k];
            symmetric[x][y] = suma;
        }
    }

    //przepisywanie do macierzy
    for(x=0; x<N; x++){
        for(y=0; y<x+1; y++){
            m[x][y] = symmetric[x][y];
            m[y][x] = symmetric[x][y];
        }
    }


    // get dominant matrix
    int i,j;
    for(i=0; i<N; i++){
        double sum = (zmp)1;
        for(j=0; j<N; j++){
            if(i != j)
                sum += fabs(m[i][j]);
        }
        int max = sum + (zmp)1;
        if (m[i][i] < 0)
            m[i][i] = - max;
        else
            m[i][i] = max;
    }

    //normalize matrix
    double max = -1.0;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            if(abs(m[i][j] > max))
                max = abs(m[i][j]);
        }
    }
    double divider = max / A_MAX_VALUE;

    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            m[i][j] /= divider;
        }
    }

    return;
}

zmp getError(zmp A[N][N], zmp x[N], zmp b[N]){
    zmp error = 0.0;
    int i,j;
    for(i=0;i<N; i++){
        zmp suma = 0.0;
        for(j=0; j<N; j++){
            suma += A[i][j] * x[j];
        }
        error += pow((suma - b[i]),2.0);
    }
    return error;
}

void multiplyMatrixVector(zmp A[N][N], zmp x[N], zmp y[N])
{
    int i,j;
    for(i=0;i<N; i++){
        zmp suma = 0.0;
        for(j=0; j<N; j++){
            suma += A[i][j] * x[j];
        }
        y[i] = suma;
    }
    return;
}



