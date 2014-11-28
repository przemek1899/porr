
#ifndef MATRIXGENERATOR_H
#define MATRIXGENERATOR_H

#define N 10 /*macierz o rozmiarze NxN*/
const double A_MAX_VALUE;
const double B_MAX_VALUE;

typedef double zmp; //używany typ zmiennoprzecinkowy
typedef const double c_zmp;

typedef zmp matrix[N][N];

zmp getAlfa(zmp m[N][N]);

void generateRandomVector(zmp* b);

void generateRandomMatrix(zmp m[N][N]);
void getSymmetricMatrix(zmp m[N][N]);
void getDiagonalMatrix(zmp m[N][N]);
void normalizeMatrix(zmp m[N][N]);

void getRichardsonMatrix(zmp m[N][N]);

void multiplyMatrixVector(zmp A[N][N], zmp* x, zmp* y);
void subtractVectors(zmp * a, zmp* b, int length);
void multiplyVectorByScalar(zmp* x, int length, zmp s);
richardsonIteration(zmp* x, zmp alfa, zmp A[N][N], c_zmp* b);

#endif
