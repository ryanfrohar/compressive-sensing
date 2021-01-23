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
int NumberFound = 0;  // Number of max indexes found

/**

Function to return inner product of a specific column of a matrix and a row vector.

vector: Mx1 vector containing float values. (float)
mulColumn: Index of the column being multiplied in the matrix by the vector. (int)

*/
float innerColMul(float vector[M], int mulColumn)
{
	float total = 0;  // Used to store the total product value of the multiplication
	
	// Loop to multiply all elements of the matrix's selected column by the vector's elements
	for(int i=0; i<M ; i++) {
		total = total + (Rand_Mat[i][mulColumn] * vector[i]);  // Increment total sum value
	}
	
	return total;  // Return total sum of the inner product multiplication
}

/**

Function to calculate the correlation of normalized vector and residual vector

*/
void calc_correlation(float correlation[N], float norms[N], float r[M]){
	float temp;  // Vector to hold inner column multiplication sum value of residual vector and a given index of random matrix
	for(int i = 0; i<N; i++){
		temp = innerColMul((float *) r, i);
		correlation[i] = fabs(temp/norms[i]);  // Calculate and store correlation value in the correlation array
	}
}

/**

Multiplies two matrices into result vector, number of columns of first matrix must equal 
number of rows of second matrix for it to work mathematically

*/
void matMultiplication(int n, float matrix1[M][N], float matrix2[N][n], float result[M][n]){
	int i,j,k;
	for(i=0;i<M;i++){
    		for(j=0;j<n;j++){
        		result[i][j]=0;  // Initialize result vector values as 0
        		for(k=0;k<N;k++){
            			result[i][j]+=matrix1[i][k] * matrix2[k][j];  // Multiply matrix1 by matrix2 and store the value in the result vector/matrix
        		}
			//printf("%d\n",result[i][j]);
		}
	}
}

/**

Subtracts two matrices of same size into result matrix.
Matricies must be same size to subtract.

*/
void matSubtraction(int matrix1[M][N],int matrix2[M][N],int result[M][N]){
	for(int i=0;i<M;i++){
    		for(int j=0;j<N;j++){
			result[i][j] = matrix1[i][j] - matrix2[i][j];  // Subtract matrix2 from matrix1 and store into result matrix
			//printf("%d\n",result[i][j]);
		}
	}	
}

/**

Function to print contents of matrix.
Used to verify that the contents are correct.

*/
void printMatrix(int m,int n, int matrix[m][n]){
	for(int i=0;i<m;i++){
    		for(int j=0;j<n;j++){
			printf("%d ", matrix[i][j]);  // Print all elements in the row of a matrix
		}
	printf("\n");  // Next line to print the next row
	}
}

/**

Function to locate index where the max value of an array exist

*/
int max_index(float *array, int size){
	int indexMax = 0;  //Index of the array where the max value exist
	float max = *(array + indexMax);  //Initialize the max as the first element of the array
	for (int i = 0; i < size; i++){
		if (*(array + i) > max)  //If current index's value is greater than the stored max value
		{
			max = *(array + i);  //Set current index's value as the max
			indexMax = i;  //Update the index value where the max value exist
		}
	}
	return(indexMax);  //Return index value of the max
}	

/**

Function to calculate the norm of a column in a matrix

*/
float norm_Col(float *array, int m, int n, int C){
	float sum = 0;  //Initialize norm sum of column value
	float *fixed = array + C ;  //Copy a specified column from the matrix
	for (int i = 0;i < m;i++){
		sum = sum + *(fixed + (i*n)) * *(fixed + i*n);  //Increment the sum with the normaized value of each element in the specified column
	}
	sum=sqrt(sum);  //Square root the summed squared values to get the norm sum
	return sum;  //Return norm sum
}

/**

Swap function that is used in the bubble sort to swap the order of array elements

*/
void swap(int *xp, int *yp){
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
	return;
}

/**

Bubble sort function used to sort max index values

*/
void bubbleSort(int *arr, int n){
	int i, j;
	for (i = 0; i < n - 1; i++){
		// Last i elements are already in place
		for (j = 0; j < n - i - 1; j++){
			if (arr[j] > arr[j + 1]){  //If element is larger than next element in array
				swap(&arr[j], &arr[j + 1]);  //Swap the placement of the elements
			}
		}
	}
	return;
}

/**

Function to add max indexes to the max index set

*/
void unionMat(int *vec, int newval) {
	// Using this function values of index are sorted and there is no need to check for repitition
	for (int i = 0;i<NumberFound;i++){
		if (*(vec + i) == newval){ 
			//Ignore if repetition
			return;
		}
	}
	*(vec + NumberFound) = newval;  //Add max index to max index set in order according to the number of max index values which have been found
	NumberFound++;  //Increment number of max index values which have been found
	bubbleSort(vec, NumberFound);  //Sort to verify that max indexes are in order in the max index set
	return;
}

/**

Function to calculate the Mean Squared Error.
Takes sparse signal and compares it to the array of max signal values and outputs the deviation average.

*/
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

Function to calculate the Sound to Noise Ratio of the signal being processed.
The ratio is a result of the log of the sum of the MSE value of the sparse signal and the array of max signal values in the sparse signal.

*/
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

/**

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
			Rand_Mat[x][y] = rand()%10;  //Populate with random values from 0-9
		}
	}
	//N=256, M=64
	float x[N];
	float y[M];
	float x_hat[N];

	int i;
	int iterationCounter;

	for (i = 0;i <N;i=i+1) {
		x[i] = i/(i+10);  //Create a normalized vector with values all <1
	}
	
	int randNum;
	//Make 6 random coeff out of N coeff in normalized vector >1 with range 2>x>24
	for (i = 0;i < S;i++){
		randNum = (int) (rand() % (N-1));
		x[randNum] = (float)(rand() % 25);
		if(x[randNum] < 2){
			x[randNum] += 15;
		}
	}

	matMultiplication(1, Rand_Mat, x, y);  //Multiply random matrix with normalized vector that represents the sparse signal with sparsity of 6.  Store into vector y.

	//PRINTING Y
	printf("Printing Y\n");
	for (i = 0;i <M;i=i+1) {
		printf("%.10f", y[i]);
		printf("\n");
	}


	//Beginning of OMP Algorithm
	float r[M];  //Residual vector
	float norms[N];  //Norm vector
	float correlation[N];  //Correlation array
	int indexSet[N];  //Index set which will contain max indexes

	NumberFound=0;  //Number of max indexes found

	for (i = 0;i < N;i++){
		x_hat[i]= 0;
		indexSet[i] = 999999; //Initialize with some value greater than any real possible value
		norms[i] = norm_Col(Rand_Mat, M, N, i); //Calculate norm of column of C
	}

	for (i = 0;i < M;i++) {
		r[i] = y[i]; //Copy the result vector y into the residual vector
	}

	printf("Algorim Begins \n");

	for(iterationCounter=0; iterationCounter<S; iterationCounter++){
		calc_correlation(correlation, norms, r);  //Calculate correlation of norm vector and residual vector and place results into correction array
		int maxIndex= max_index(correlation, N);  //Max index is the index of the max value in the correlation array
		printf("Max Index: %d\n", maxIndex);

		unionMat(indexSet, maxIndex);

		float rand_Mat_Hat[M*]



		unionMat(indexSet, maxIndex);  //Add max to index set
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



