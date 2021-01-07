#include <stdio.h>
#include "stdio.h"
#include <stdlib.h>
#include "math.h"
/*
 Multiplies two matrixes into result vector, number of columns of first matrix must equal 
number of rows of second matrix for it to work mathematically
*/
void MatMultiplication(int M,int N,int n,int matrix1[M][N], int matrix2[N][n], int result[M][n]){
	int i,j,k;
	for(i=0;i<M;i++){
    		for(j=0;j<n;j++){
        		result[i][j]=0;
        		for(k=0;k<N;k++){
            			result[i][j]+=matrix1[i][k] * matrix2[k][j];
        		}
			//printf("%d\n",result[i][j]);
		}
	}

}

/*
	Subtracts two matrixes of same size into result

*/
void MatSubtraction(int M,int N, int matrix1[M][N],int matrix2[M][N],int result[M][N]){
	//matricies must be same size to subtract
	for(int i=0;i<M;i++){
    		for(int j=0;j<N;j++){
			result[i][j] = matrix1[i][j] - matrix2[i][j];
			//printf("%d\n",result[i][j]);
		}
	}
	
	
}
//to check for correct contents of matrix
void printMatrix(int m,int n, int matrix[m][n]){
	for(int i=0;i<m;i++){
    		for(int j=0;j<n;j++){
			printf("%d ", matrix[i][j]);
		}
	printf("\n");
	}
}
		
int max_index(float *array, int size){
	int indexMax = 0;
	float max = *(vector + indexMax);
	for (int i = 0; i < size; i++){
		if (*(vector + i) > max)
		{
			max = *(vector + i);
			indexMax = i;
		}
	}
	return(indexMax);
}	

float norm_Col(float *array, int m, int n, int C){
	float sum = 0;
	float *fixed = array + C ;
	for (int i = 0;i < m;i++){
		sum = sum + *(fixed + (i*n)) * *(fixed + i*n);
	}
	sum=sqrt(sum);
	return sum;
}


void main(){
	/*
	int arr[2][3] = {{3,2,4}, {-4,5,1}};
	int arr1[3][4] = {{3,0,-3,6},{7,5,-4,4},{-2,2,-1,1}};
	int result[2][4] = {0};
	MatMultiplication(2,3,4,arr,arr1,result);
	printMatrix(2,4,result);
	
	
	int arr[2][2] = {{4,3}, {2,1}};
	int arr1[2][2] = {{1,2},{1,1}};
	int res[2][2] = {0};
	MatSubtraction(2,2,arr,arr1,res);
	printMatrix(2,2,res);
	*/
	
}


