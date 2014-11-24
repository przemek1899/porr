
#ifndef MATRIXGENERATOR_H
#define MATRIXGENERATOR_

#define N 10 /*macierz o rozmiarze NxN*/
const int A_MAX_VALUE = 10;
const int A_MIN_VALUE = -10;
const int B_MAX_VALUE = 10*N;
const int B_MIN_VALUE = -10*N;

//we wstępnej fazie załóżmy, że alfa jest takie
const float ALFA = 0.5f;

typedef double zmp; //używany typ zmiennoprzecinkowy

typedef zmp matrix[N][N];

matrix* generateRandomMatrix();
matrix* getSymmetricMatrix(zmp[][N]);
void getDiagonalMatrix(zmp[][N]);
matrix* multiplyMatrixVector(zmp A[][N], zmp* x);
zmp* subtractVectors(zmp * a, zmp* b, int length);
zmp* multiplyVectorByScalar(zmp* a, int length, zmp s);

#endif
