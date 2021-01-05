
//  Created by Archit Bhatia on 2020-12-25.

#include <stdio.h>
#include <stdlib.h>

#define M 3 // Amount of measurements taken
#define N 5 // Amount of samples
#define S 6 // Sparsity
#define amount_Found 16 // amount of elements found
#define iterations 11 // number of iterations
int Matrix[M][N]; //Matrix composed of the measurements and samples



/*
Takes a matrix and prints the transpose of the matrix
*/

void Transpose(int inputMatrix[M][N], int TransposeMatrix[N][M]){

    int i, j;
    for (i = 0; i < N; i++){
        for(j = 0; j < M; j++){
            TransposeMatrix[i][j] = inputMatrix[j][i];
        }
    }
}

void main(){
    
    // populates the starting matrix with random values
    for(int x = 0; x < M; x++){
        for(int y = 0; y < N; y++){
            Matrix[x][y] = rand()%100; // randomizes the values being filled with up to 100
            printf("%d ", Matrix[x][y]); // prints the input matrix
        }
        printf("\n");
    }
    printf("\n");
    
    
    int B[N][M], i, j;
    Transpose(Matrix,B); //calls the transpose function
    
    //prints the transpose matrix
    for(i = 0; i < N; i++){
        for(j = 0; j < M; j++){
        	 printf("%d ", B[i][j]);
        }
        printf("\n");
    }
     
    
}

