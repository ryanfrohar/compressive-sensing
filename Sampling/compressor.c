#include <stdio.h>
#include "stdio.h"
#include <stdlib.h>
#include <math.h>

#define M 64 // Amount of measurements
#define N 256 // Amount of samples
#define S 15 // Sparsity



void matMultiplication(int m, int n, int p, int matrix1[m][n], int matrix2[n][p], int result[m][p]){
	int i,j,k;
	for(i=0;i<m;i++){
    		for(j=0;j<p;j++){
        		result[i][j]=0;  // Initialize result vector values as 0
        		for(k=0;k<n;k++){
            			result[i][j]+=matrix1[i][k] * matrix2[k][j];  // Multiply matrix1 by matrix2 and store the value in the result vector/matrix
        		}
			//printf("%d\n",result[i][j]);
		}
	}
}

int main(){
	int Rand [M][N];
	int compressedX[M];
	int xsig [N];
		
	FILE *phi;
	phi = fopen("phi.txt", "r");
	for(int row = 0; row < M; row++){
		for(int col = 0; col < N; col++){
				fscanf(phi, "%d", &Rand[row][col]); //Populate with random values from 0-9
		}
	}
	fclose(phi);	
	
	FILE *myFile;
	myFile = fopen("samples.txt", "r");
	for (int i = 0; i < N; i++){
		fscanf(myFile, "%d", &xsig[i]);
	}
	fclose(myFile);
	
	matMultiplication(M, N, 1, Rand, xsig, compressedX);
	
	FILE *c;
	c = fopen("compressed.txt", "w");
	for (int z = 0;z <M;z=z+1) {
		fprintf(c, "%d\n", compressedX[z]);
	}
}
