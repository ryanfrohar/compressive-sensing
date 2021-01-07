#include <stdio.h>
#include "stdio.h"
#include <stdlib.h>
#include "math.h"

#define M 3 // Amount of measurements taken
#define N 5 // Amount of samples
#define S 6 // Sparsity
#define amount_Found 16 // amount of elements found
#define iterations 11 // number of iterations
int Matrix[M][N]; //Matrix composed of the measurements and samples

void calc_correlation(int N,int correlation[N],int norms[N],float inner_sum[N]){
	for(int i = 0; i<N; i++){
		correlation[i] = fabs(inner_sum[i]/norms[i]);
	}
}

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
void union(int *vec, int newval) {
	// Using this function values of index are sorted and there is no need to check for repitition
	for (int i = 0;i<number_of_finded;i++){
		if (*(vec + i) == newval){ 
			//Ignore if repetition
			return;
		}
	}
	*(vec + number_of_finded) = newval; 
	number_of_finded++;
	bubbleSort(vec, number_of_finded);
	return;
}

/**

@Ross Matthew
Function to return inner product of a specific column of a matrix and a row vector.

matrix: 2x2 matrix containing float values. (float)
vector: 2x1 vector containing float values. (float)
matrixRows: Number of rows in the matrix being used. (int)
matrixColumns: Number of columns in the matrix being used. Same as the vector size. (int)
mulColumn: Index of the column being multiplied in the matrix. (int)

**/

float innerColMul(float matrix, float vector, int matrixRows, int matrixColumns, int mulColumn)
{
	float total = 0;  // Used to store the total product value of the multiplication
	
	// Loop to multiply all elements of the matrix's selected column by the vector's elements
	for(int i=0; i<M ; i++) {
		total = total + (matrix[i][mulColumn] * vector[i]);
	}
	
	return total;
}

/**

@Ross Matthew
Function to calculate the Mean Squared Error.
Takes sparse signal and compares it to the array of max signal values and outputs the deviation average.

**/


float MSE(float sparse, float maxIndexes, int length)
{
	float mse = 0;  // Initialize mean squared error value
	
	for( int i=0 ; i<length ; i++)
	{
		mse += (sparse[i] - maxIndexes[i]) ^ 2;  // Add the squared difference of each value in the array/vector
	}
	
	return mse/length;  // return the average deviation based on the length of the entire array/vector being compared
}

/**

@Ross Matthew
Function to calculate the Sound to Noise Ratio of the signal being processed.
The ratio is a result of the log of the sum of the MSE value of the sparse signal and the array of max signal values in the sparse signal.

**/

float SNR( float normSparse, float maxSparseIndexes, int length)
{
	float signal = 0;  // Initialize signal, which is the sum of all the squared normalized sparse signal values
	float snr = 0;  // Initialized value for signal to noise ratio
	float mse = MSE(normSparse, maxSparseIndexes, N);  // Calculate the MSE value for the normalized sparse signal and the array of max signal values
	
	for( int i=0 ; i<length ; i++)
	{
		signal += (normSparse[i] * normSparse[i]);  // Sum the squared normalized sparse signal values
	}
	
	snr = 10 * log10(signal / mse);  // Calculate SNR
	return snr;
}

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


void testMarko(){
	/**
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

int main(){
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
	return 0; 
}



