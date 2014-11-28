#include <gsl/gsl_rng.h>
#include <math.h>
#include <float.h>
#include "matrixGenerator.h"

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

void generateRandomVector(zmp* vector, zmp a, zmp b){
    gsl_rng * generator;
    generator = gsl_rng_alloc(gsl_rng_default);
    gsl_rng_set (generator, N); //ustawienie ziarna

    int x;
    for(x=0; x<N; x++){
        vector[x] = (b-a) * gsl_rng_uniform(generator) + a; //B_MAX_VALUE * ((2*gsl_rng_uniform(generator))-1);
    }

    gsl_rng_free(generator);
    return;
}

void generateRandomMatrix(zmp m[N][N]){

    gsl_rng * generator;
    generator = gsl_rng_alloc(gsl_rng_default);
    gsl_rng_set (generator, N*N); //ustawienie ziarna

    int x,y;//x - wiersze, y - kolumny

    for(x=0; x<N; x++){
        for(y=0; y<N; y++){
            m[x][y] =  (2*gsl_rng_uniform(generator))-1;
        }
    }
    gsl_rng_free(generator);
    return;
}

void getSymmetricMatrix(zmp m[N][N]){ //zmp (*m)[N]

    int x,y; //x - wiersze, y - kolumny
    int k;
    matrix symmetric;
    //zerowanie macierzy
    for(x=0; x<N; x++){
        for(y=0; y<N; y++){
            symmetric[x][y] = 0.0;
        }
    }

    //tutaj będzie można zoptymalizować algorytm ponieważ w pętli niektóre mnożenia elementów macierzy powatarzają się
    //do sprawdzenia poniższa metoda

    for(x=0; x<N; x++){
        for(y=0; y<N; y++){
            for(k=0; k<N; k++){
                symmetric[x][y] += m[x][k]*m[y][k];
               /* if (x==5){
                    printf("poj %f %f %f %f\n", m[x][k]*m[y][k], m[x][k], m[y][k], symmetric[x][y]);
                }*/
            }
        }
    }
    //przepisywanie do macierzy m
    for(x=0; x<N; x++){
        for(y=0; y<N; y++){
            m[x][y] = symmetric[x][y];
        }
    }
    return;
}

void getDiagonalMatrix(zmp m[][N]){ //zmp (*m)[N]

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
    return;
}

void normalizeMatrix(zmp m[N][N]){
    //find the largest abs element in the matrix
    int i,j;
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


void getRichardsonMatrix(zmp m[N][N]){
    generateRandomMatrix(m);
    int i,j;
    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            printf("%f ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    getSymmetricMatrix(m);
    getDiagonalMatrix(m);
    normalizeMatrix(m);
    return;
}

void multiplyMatrixVector(zmp A[N][N], zmp* x, zmp* y) // macierz A o wymiarach NxN, wektor x o długości N
{
    int i,j;
    for(i=0;i<N; i++){
        zmp suma = 0.0f;
        for(j=0; j<N; j++){
            suma += A[i][j] * x[j];
        }
        y[i] = suma;
    }
    return;
}

/*
  metoda subtractVectors odejmuje od wektora a wektor b - wynik zapisuje w wektorze a
  */
void subtractVectors(zmp * a, zmp* b, int length){
    int i;
    for (i=0; i<length; i++){
        a[i] -= b[i];
    }
    return;
}

/*
  metoda multiplyVectorByScalar zapisuje wynik w wektorze a
  */
void multiplyVectorByScalar(zmp* a, int length, zmp s){
    int i;
    for(i=0; i<length; i++){
        a[i] *= s;
    }
    return;
}

richardsonIteration(zmp* x, zmp alfa, zmp A[N][N], c_zmp* b){
    zmp Ax[N];
    multiplyMatrixVector(A, x, Ax);
    subtractVectors(Ax, b, N);
    multiplyVectorByScalar(Ax, N, alfa);
    subtractVectors(x, Ax, N);
    return;
}


