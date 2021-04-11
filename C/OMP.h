#ifndef OMP_H_
#define OMP_H_
#include "ap_cint.h"
#define M 64 // Amount of measurements
#define N 256 // Amount of samples
#define S 12 // Sparsity
#define SHIFT_AMOUNT 16 // 2^16 = 65536
#define SHIFT_MASK ((1 << SHIFT_AMOUNT) - 1) // 65535 (all LSB set, all MSB clear)
typedef float din_t;
typedef int16 din_tt;
typedef int24 dout_t;

int OMP(float randy [M][N], int xsig[M], int reconstructedX[N]);
//void inputRand(float Rand [M][N]);

#endif

