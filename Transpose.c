//
//  main.c
//  project
//
//  Created by Archit Bhatia on 2020-12-25.
//

#include <stdio.h>

/*
Takes a matrix and prints the transpose of the matrix
*/

void Transpose(int M, int N, int inputMatrix[M][N], int TransposeMatrix[N][M]){

    int i, j;
    for (i = 0; i < M; i++){
        for(j = 0; j < N; j++){
            TransposeMatrix[i][j] = inputMatrix[j][i];
        }
    }
}

void main(){

    int A[3][3] = {{1,2,3},
                    {1,2,3},
                    {1,2,3}};
    int B[3][3], i, j;
    Transpose(3,3,A,B);
    
    
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
        	 printf("%d ", B[i][j]);
        }
        printf("\n");
    }
    
}

