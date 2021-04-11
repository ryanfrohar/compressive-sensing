#ifndef OMP_H_
#define OMP_H_

#define M 64 // Amount of measurements
#define N 256 // Amount of samples
#define S 15 // Sparsity

int OMP(float randy [M][N], int xsig[M], int reconstructedX[N]);
//void inputRand(float Rand [M][N]);


#endif

