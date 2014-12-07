
#ifndef MATRIXGENERATOR_H
#define MATRIXGENERATOR_H

#define N 2000 /*macierz o rozmiarze NxN*/
const double A_MAX_VALUE;
const double B_MAX_VALUE;

typedef double zmp; //używany typ zmiennoprzecinkowy

typedef zmp matrix[N][N];

zmp getAlfa(zmp m[N][N]);

void generateRandomVector(zmp vector[N], zmp a, zmp b);

void getRichardsonMatrix(zmp m[N][N], zmp symmetric[N][N]);

void multiplyMatrixVector(zmp A[N][N], zmp x[N], zmp y[N]) ;
zmp getError(zmp A[N][N], zmp x[N], zmp b[N]);

#endif

