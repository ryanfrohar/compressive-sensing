#include <stdio.h>
#include "stdio.h"
#include <stdlib.h>
#include "math.h"

#define M 64 // Amount of measurements
#define N 256 // Amount of samples
#define S 6 // Sparsity

//ENV Variables
float Rand_Mat[M][N]; //Matrix composed of the measurements and samples
int NumberFound = 0;  // Number of max indexes found
float MAX_RAND=7.0;
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
void matMultiplication(int m, int n, int p, float matrix1[m][n], float matrix2[n][p], float result[m][p]){
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
void printMatrix(int m,int n, float matrix[m][n]){
	for(int i=0;i<m;i++){
    		for(int j=0;j<n;j++){
			printf("%f ", matrix[i][j]);  // Print all elements in the row of a matrix
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
void transpose(int m, int n, float inputMatrix[m][n], float transposeMatrix[n][m]){

    int i, j;
    for (i = 0; i < n; i++){
        for(j = 0; j < m; j++){
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

/**
int main(){

	//srand((unsigned int)time(NULL));
	// populates the starting matrix with random values
	for(int x = 0; x < M; x++){
		for(int y = 0; y < N; y++){
			Rand_Mat[x][y] =  (float) rand()/(float)(RAND_MAX) * MAX_RAND; //Populate with random values from 0-9
		}
	}
	//printMatrix(M, N, Rand_Mat);
	//N=256, M=64
	float x[N];
	float y[M];
	float x_hat[N];

	int i, j;
	int iterationCounter;

	for (i = 0;i <N;i=i+1) {
		x[i] = 0;  //Create a normalized vector with values all <1
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

	matMultiplication(M, N, 1, Rand_Mat, x, y);  //Multiply random matrix with normalized vector that represents the sparse signal with sparsity of 6.  Store into vector y.

	//PRINTING Y
	printf("Printing X\n");
	for (i = 0;i <N;i=i+1) {
		printf("%.10f", x[i]);
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

	for(iterationCounter=0; iterationCounter<1; iterationCounter++){
		calc_correlation(correlation, norms, r);  //Calculate correlation of norm vector and residual vector and place results into correction array
		int maxIndex= max_index(correlation, N);  //Max index is the index of the max value in the correlation array
		printf("Max Index: %d\n", maxIndex);
		unionMat(indexSet, maxIndex);

		float rand_Mat_Hat[M][NumberFound];
		float rand_Mat_Transpose[NumberFound][M];
		float transpose_By_Y[NumberFound];
		float rand_Mat_Squared[NumberFound][NumberFound];

		for ( i = 0;i < M;i++){ // Get a copy of A with only selected index
			for ( j = 0;j < NumberFound;j++) {
				rand_Mat_Hat[i*NumberFound][j] = Rand_Mat[i][indexSet[j]];
			}
		}

		transpose(M, NumberFound, rand_Mat_Hat, rand_Mat_Transpose);

		matMultiplication(NumberFound, M, 1, rand_Mat_Transpose, y, transpose_By_Y);

		matMultiplication(NumberFound, M, NumberFound, rand_Mat_Transpose, rand_Mat_Hat, rand_Mat_Squared);

		printMatrix(NumberFound, NumberFound, rand_Mat_Squared);

		


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
*/

// Function to get cofactor of A[p][q] in temp[][]. n is current 
// dimension of A[][] 
void getCofactor(int sz, int A[sz][sz], int temp[sz][sz], int p, int q, int n) 
{ 
	int i = 0, j = 0; 

	// Looping for each element of the matrix 
	for (int row = 0; row < n; row++) 
	{ 
		for (int col = 0; col < n; col++) 
		{ 
			// Copying into temporary matrix only those element 
			// which are not in given row and column 
			if (row != p && col != q) 
			{ 
				temp[i][j++] = A[row][col]; 

				// Row is filled, so increase row index and 
				// reset col index 
				if (j == n - 1) 
				{ 
					j = 0; 
					i++; 
				} 
			} 
		} 
	} 
} 

/* Recursive function for finding determinant of matrix. 
n is current dimension of A[][]. */
int determinant(int q, int A[q][q], int n) 
{ 
	int D = 0; // Initialize result 

	// Base case : if matrix contains single element 
	if (n == 1){
		return A[0][0]; 
	}

	int temp[q][q]; // To store cofactors 

	int sign = 1; // To store sign multiplier 

	// Iterate for each element of first row 
	for (int ii = 0; ii < n; ii++) 
	{ 
		// Getting Cofactor of A[0][f] 
		getCofactor(q, A, temp, 0, ii, n); 
		D += sign * A[0][ii] * determinant(q, temp, n - 1); 

		// terms are to be added with alternate sign 
		sign = -sign; 
	} 

	return D; 
} 

// Function to get adjoint of A[N][N] in adj[N][N]. 
void adjoint(int q, int A[q][q],int adj[q][q]) 
{ 
	if (q == 1) 
	{ 
		adj[0][0] = 1; 
		return; 
	} 

	// temp is used to store cofactors of A[][] 
	int sign = 1, temp[q][q]; 

	for (int i=0; i<q; i++) 
	{ 
		for (int j=0; j<q; j++) 
		{ 
			// Get cofactor of A[i][j] 
			getCofactor(q, A, temp, i, j, q); 

			// sign of adj[j][i] positive if sum of row 
			// and column indexes is even. 
			sign = ((i+j)%2==0)? 1: -1; 

			// Interchanging rows and columns to get the 
			// transpose of the cofactor matrix 
			adj[j][i] = (sign)*(determinant(q, temp, q-1)); 
		} 
	} 
} 

// Function to calculate and store inverse, returns false if 
// matrix is singular 
int inverse(int q, int A[q][q], float inverse[q][q]) 
{ 
	// Find determinant of A[][] 
	int det = determinant(q, A, q); 
	if (det == 0){ 
		return 0; 
	} 

	// Find adjoint 
	int adj[q][q]; 
	adjoint(q, A, adj); 

	// Find Inverse using formula "inverse(A) = adj(A)/det(A)" 
	for (int i=0; i<q; i++){
		for (int j=0; j<q; j++){
			inverse[i][j] = adj[i][j]/((float) det); 
		}
	}

	return 1; 
} 


// Driver program 
int main() 
{ 
	int A[4][4] = { {5, -2, 2, 7}, 
					{1, 0, 0, 3}, 
					{-3, 1, 5, 0}, 
					{3, -1, -9, 4}}; 

	int adj[4][4]; // To store adjoint of A[][] 

	float inv[4][4]; // To store inverse of A[][] 

	adjoint(4, A, adj); 

	if (inverse(4, A, inv)){
		printMatrix(4, 4, inv);
	}

	return 0; 
} 



