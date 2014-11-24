#include <gsl/gsl_rng.h>
#include <float.h>
#include <math.h>
#include "matrixGenerator.h"

matrix* generateRandomMatrix(){

    gsl_rng * generator;
    generator = gsl_rng_alloc(gsl_rng_default);
    gsl_rng_set (generator, N*N); //ustawienie ziarna

    matrix m;

    int x,y;//x - wiersze, y - kolumny

    for(x=0; x<N; x++){
        for(y=0; y<N; y++){
            m[x][y] =  DBL_MAX *gsl_rng_uniform(generator);
        }
    }

    gsl_rng_free(generator);
    return &m;
}

matrix* getSymmetricMatrix(zmp m[][N]){ //zmp (*m)[N]
    matrix symmetric;

    int x,y; //x - wiersze, y - kolumny
    int k;

    //tutaj będzie można zoptymalizować algorytm ponieważ w pętli niektóre mnożenia elementów macierzy powatarzają się
    //do sprawdzenia poniższa metoda

    for(x=0; x<N; x++){
        for(y=0; y<N; y++){
            for(k=0; k<N; k++)
                symmetric[x][y] += m[x][k]*m[y][k];
        }
    }
    return &symmetric;
}

void getDiagonalMatrix(zmp m[][N]){ //zmp (*m)[N]

    int i,j;
    for(i=0; i<N; i++){
        double sum = (zmp)1;
        for(j=0; j<N; j++){
            if(i != j)
                sum += fabs(m[i][j]);
        }
        m[i][i] = sum + (zmp)1; //na razie przyjmujemy, że zwiększamy element przekątnej macierzy o 1
        // ale może to też być liczba ujemna o wartości bezwględnej większej od fabs(sum)
    }
}

matrix* multiplyMatrixVector(zmp A[][N], zmp* x) // macierz A o wymiarach NxN, wektor x o długości N
{
    zmp result[N];

    int i,j;
    for(i=0;i<N; i++){
        zmp suma = 0.0f;
        for(j=0; j<N; j++){
            suma += A[i][j] * x[j];
        }
        result[i] = suma;
    }
    return &result[0];
}


zmp* subtractVectors(zmp * a, zmp* b, int length){
    zmp result[length];
    int i;
    for (i=0; i<N; i++){
        result[i] = a[i] - b[i];
    }
    return &result[0];
}

zmp* multiplyVectorByScalar(zmp* a, int length, zmp s){
    int i;
    for(i=0; i<length; i++){
        a[i] *= s;
    }
    return a;
}



