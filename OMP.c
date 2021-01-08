#include <stdio.h>
#include "stdio.h"
#include <stdlib.h>
#include "math.h"

#define M 64 // Amount of measurements
#define N 256 // Amount of samples
#define S 6 // Sparsity
#define amount_Found 15 // amount of elements found

//ENV Variables
float Rand_Mat[M][N]; //Matrix composed of the measurements and samples
int NumberFound = 0;

/**
Function to return inner product of a specific column of a matrix and a row vector.

matrix: 2x2 matrix containing float values. (float)
vector: 2x1 vector containing float values. (float)
matrixRows: Number of rows in the matrix being used. (int)
matrixColumns: Number of columns in the matrix being used. Same as the vector size. (int)
mulColumn: Index of the column being multiplied in the matrix. (int)

**/

float innerColMul(float vector[M], int mulColumn)
{
	float total = 0;  // Used to store the total product value of the multiplication
	
	// Loop to multiply all elements of the matrix's selected column by the vector's elements
	for(int i=0; i<M ; i++) {
		total = total + (Rand_Mat[i][mulColumn] * vector[i]);
	}
	
	return total;
}


void calc_correlation(float correlation[N],float norms[N], float r[M]){
	float temp;
	for(int i = 0; i<N; i++){
		temp = innerColMul((float *) r, i);
		correlation[i] = fabs(temp/norms[i]);
	}
}

/*
 Multiplies two matrixes into result vector, number of columns of first matrix must equal 
number of rows of second matrix for it to work mathematically
*/

void matMultiplication(int n, float matrix1[M][N], float matrix2[N][n], float result[M][n]){
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
void matSubtraction(int matrix1[M][N],int matrix2[M][N],int result[M][N]){
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
	float max = *(array + indexMax);
	for (int i = 0; i < size; i++){
		if (*(array + i) > max)
		{
			max = *(array + i);
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


void swap(int *xp, int *yp){
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
	return;
}

void bubbleSort(int *arr, int n){
	int i, j;
	for (i = 0; i < n - 1; i++){
		// Last i elements are already in place
		for (j = 0; j < n - i - 1; j++){
			if (arr[j] > arr[j + 1]){
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
	return;
}


void unionMat(int *vec, int newval) {
	// Using this function values of index are sorted and there is no need to check for repitition
	for (int i = 0;i<NumberFound;i++){
		if (*(vec + i) == newval){ 
			//Ignore if repetition
			return;
		}
	}
	*(vec + NumberFound) = newval; 
	NumberFound++;
	bubbleSort(vec, NumberFound);
	return;
}



/**

@Ross Matthew
Function to calculate the Mean Squared Error.
Takes sparse signal and compares it to the array of max signal values and outputs the deviation average.

**/


float MSE(float sparse[N], float maxIndexes[N], int length)
{
	float mse = 0;  // Initialize mean squared error value
	for( int i=0 ; i<length ; i++)
	{
		mse += (sparse[i] - maxIndexes[i])*(sparse[i] - maxIndexes[i]);  // Add the squared difference of each value in the array/vector
	}
	
	return mse/length;  // return the average deviation based on the length of the entire array/vector being compared
}

/**

@Ross Matthew
Function to calculate the Sound to Noise Ratio of the signal being processed.
The ratio is a result of the log of the sum of the MSE value of the sparse signal and the array of max signal values in the sparse signal.

**/

float SNR( float normSparse[N], float maxSparseIndexes[N], int length)
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

void transpose(float inputMatrix[M][N], float transposeMatrix[N][M]){

    int i, j;
    for (i = 0; i < N; i++){
        for(j = 0; j < M; j++){
            transposeMatrix[i][j] = inputMatrix[j][i];
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
			Rand_Mat[x][y] = rand()%10; // randomizes the values being filled with up to 10
			//printf("%d ", Rand_Mat[x][y]); // prints the input matrix
		}
		//printf("\n");
	}
	//N=256, M=64
	float x[N];
	float y[M];
	float x_hat[N];

	int i;
	int iterationCounter;

	for (i = 0;i <N;i=i+1) {
		x[i] = i/(i+10);
		//printf("%f", x[i]);
		//printf("\n");
	}
	
	int randNum;
	// only 6 out of N coeff of x are nonzero
	for (i = 0;i < S;i++){
		randNum = (int) (rand() % (N-1));
		x[randNum] = (float)(rand() % 25);
		if(x[randNum] < 2){
			x[randNum] += 15;
		}
	}

	matMultiplication(1, Rand_Mat, x, y);

	//PRINTING X
	printf("Printing Y\n");
	for (i = 0;i <M;i=i+1) {
		printf("%.10f", y[i]);
		printf("\n");
	}


	//Beginning of OMP Algorithm
	float r[M];
	float norms[N];
	float correlation[N];
	int indexSet[N];

	NumberFound=0;

	for (i = 0;i < N;i++){
		x_hat[i]= 0;
		indexSet[i] = 999999; //Initialize with some value less than all
		norms[i] = norm_Col(Rand_Mat, M, N, i); //Calculate norm of column of C
	}

	for (i = 0;i < M;i++) { //Init residual vector
		r[i] = y[i]; //r = x;
	}

	printf("Algorim Begins \n");

	for(iterationCounter=0; iterationCounter<S; iterationCounter++){
		calc_correlation(correlation, norms, r);
		int maxIndex= max_index(correlation, N);
		printf("Max Index: %d\n", maxIndex);
		unionMat(indexSet, maxIndex);
	}
	
	printf("Printing correlation\n");
	for (i = 0;i <N;i=i+1) {
		printf("%.10f\n", correlation[i]);
	}
	
	printf("Printing index set\n");
	for (i = 0;i <N;i=i+1) {
		printf("%d\n", indexSet[i]);
	}
	
	return 0; 
}



