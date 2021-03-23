#include <stdio.h>
#include "stdio.h"
#include <stdlib.h>
#include <math.h>

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
float innerProduct(float vector[M], int mulColumn){
	
	float total = 0;  // Used to store the total product value of the multiplication
	float *index = Rand_Mat + mulColumn;
	// Loop to multiply all elements of the matrix's selected column by the vector's elements
	for(int i=0; i<M ; i++) {

		//total = total + *(index + i*N) * *(vector + i);
		total = total + (Rand_Mat[i][mulColumn] * vector[i]);  // Increment total sum value
	}
	
	return total;  // Return total sum of the inner product multiplication
}

/**

Function to calculate the correlation of normalized vector and residual vector

*/
void correlationCalc(float correlation[N], float norms[N], float r[M]){
	float temp;  // Vector to hold inner column multiplication sum value of residual vector and a given index of random matrix
	for(int i = 0; i<N; i++){
		temp = innerProduct((float *) r, i);
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
void matSubtraction(int m, int n, float matrix1[m][n], float matrix2[m][n], float result[m][n]){
	for(int i=0;i<m;i++){
    		for(int j=0;j<n;j++){
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

Function to print contents of matrix.
Used to verify that the contents are correct.

*/
void printMatrixInt(int m,int n, int matrix[m][n]){
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
int maxIndex(int size, float array[size]){
	int indexMax = 0;  //Index of the array where the max value exist
	float max = array[indexMax];  //Initialize the max as the first element of the array
	for (int i = 0; i < size; i++){
		if (array[i] > max)  //If current index's value is greater than the stored max value
		{
			max = array[i];  //Set current index's value as the max
			indexMax = i;  //Update the index value where the max value exist
		}
	}
	return indexMax;  //Return index value of the max
}	

/**

Function to calculate the norm of a column in a matrix

*/
float normCol(float *array, int m, int n, int C){
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
void bubbleSort(int n, int arr[n]){
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
		if (vec[i] == newval){ 
			//Ignore if repetition
			return;
		}
	}

	vec[NumberFound] = newval;  //Add max index to max index set in order according to the number of max index values which have been found
	NumberFound=NumberFound+1;  //Increment number of max index values which have been found
	bubbleSort(vec, NumberFound);  //Sort to verify that max indexes are in order in the max index set
	return;
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
float determinant(int q, float A[q][q], int n) 
{ 
	float D = 0; // Initialize result 

	// Base case : if matrix contains single element 
	if (n == 1){
		return A[0][0]; 
	}

	float temp[q][q]; // To store cofactors 

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
void adjoint(int q, float A[q][q], float adj[q][q]) 
{ 
	if (q == 1) 
	{ 
		adj[0][0] = 1; 
		return; 
	} 

	// temp is used to store cofactors of A[][] 
	int sign = 1;
	float temp[q][q]; 

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
int inverse(int q, float A[q][q], float inverse[q][q]) 
{ 
	// Find determinant of A[][] 
	float det = determinant(q, A, q); 
	if (det == 0){ 
		inverse[0][0]= 1/A[0][0];
		return 1;
	} 

	// Find adjoint 
	float adj[q][q]; 
	adjoint(q, A, adj); 

	// Find Inverse using formula "inverse(A) = adj(A)/det(A)" 
	for (int i=0; i<q; i++){
		for (int j=0; j<q; j++){
			inverse[i][j] = adj[i][j]/((float) det); 
		}
	}

	return 1; 
} 
void magnitude(int p, float matrix1[p], float result[1]){
	float temp=0.0;
	for(int i =0; i<p; i++){
		//printf("Matrix index %d is %f\n", i, matrix1[i]);
		temp+= matrix1[i]*matrix1[i];
	}
	//printf("Temp variable in magnitude is %f\n", temp);
	result[0]=sqrt(temp);
	return;
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
// Driver program 
int testInverse() { 
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

/**

The QR algotrithm decomposes a randMatSquared matrix (A) into two matrices Q and R by using the Gram-Schmidt process.
It is decomposed into an orthogonal and a triangular matrix.

*/


void qr(int n, float q[n][n], float R[n][n]) {

	//Initialize R to be equal to (transpose of Q) x Q 

	for (int m = 0;m < n;m++) {
		for (int i = 0;i < m;i++){
			float product=0;
			for(int z = 0; z<n;z++){
				product+= q[z][i] * q[z][m];
			}
			R[i][m] = product;
		}

		for (int i = 0;i < n;i++) {
			float result = 0;

			//Store R x Q of column into QinR
			for (int j = 0;j < m;j++){
				result = result + q[i][j] * R[j][m];
			}

			//Subtract QinR by Q
			q[i][m] = q[i][m] - result;
		}

		//Store norm of Q in R
		R[m][m] = normCol(q, n, n, m);

		//Divide Q by norm of Q which is stored in R
		for (int i = 0;i < n;i++) {
			q[i][m] = q[i][m] / R[m][m];
		}
	}

	return;
}

void backSubstitution(int n, float R[n][n], float d[n], float x_hat[M]) {

	for (int i = n - 1;i >= 0;i--){
		x_hat[i] = d[i] / R[i][i];
		
		for (int j = 0;j < i;j++){
			d[j] = d[j] - R[j][i] * x_hat[i];
		}
	}
	return;
}

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
	int ii;

	for (i = 0;i <N;i=i+1) {
		x[i] = 0;  //Create a normalized vector with values all <1
	}
	
	x[2]=15.0;
	x[10]= 18.0;
	x[255]= 14.0;
	x[252]= 12.0;
	x[100]=13.0;
	x[150]= 14.0;

	matMultiplication(M, N, 1, Rand_Mat, x, y);  //Multiply random matrix with normalized vector that represents the sparse signal with sparsity of 6.  Store into vector y.
	
	//PRINTING X
	printf("Printing X\n");
	for (i = 0;i <N;i=i+1) {
		printf("%f", x[i]);
		printf("\n");
	}
	

	//Beginning of OMP Algorithm
	float r[M];  //Residual vector
	float norms[N];  //Norm vector
	float correlation[N];  //Correlation array
	int indexSet[N];  //Index set which will contain max indexes

	//NumberFound=0;  //Number of max indexes found

	for (i = 0;i < N;i++){
		x_hat[i]= 0;
		indexSet[i] = 99999; //Initialize with some value greater than any real possible value
		norms[i] = normCol(Rand_Mat, M, N, i); //Calculate norm of column of i
	}

	for (i = 0;i < M;i++) {
		r[i] = y[i]; //Copy the result vector y into the residual vector
		//printf("%f\n", y[i]);
	}

	printf("Algorim Begins \n");
	//for(ii=0;ii<100;ii++)
	for(iterationCounter=0; iterationCounter<S+1; iterationCounter++){
		printf("Iteration %d\n", iterationCounter);
		//printMatrix(M, 1, r);
		correlationCalc(correlation, norms, r);  //Calculate correlation of norm vector and residual vector and place results into correction array
		//printMatrix(N, 1, correlation);

		int maximumIndex= maxIndex(N, correlation);  //Max index is the index of the max value in the correlation array
		//printf("MAX CORRELATION IS %f\n", correlation[maxIndex]);
		//printf("Max Index: %d\n", maxIndex);
		unionMat(indexSet, maximumIndex);
		//printMatrixInt(N, 1, indexSet);


		float rand_Mat_Hat[M*NumberFound];
		float rand_Mat_Transpose[NumberFound][M];
		float rand_Mat_Squared[NumberFound][NumberFound];
		float q[NumberFound][NumberFound];
		float resultQR[NumberFound][NumberFound];
		float qt[NumberFound][NumberFound];
		float yQt[NumberFound];
		float transpose_By_Y[NumberFound];
		float x_hat_temp[M];
		
		/**
		

		float inv_By_TransposeY[NumberFound];
		float randMatHat_By_Inv[M];
		float x_bar[M];
		float x_bar_Mag[1];
		float residualX[M];
		**/
		//printf("Number found is %d\n", NumberFound);
		for (i = 0;i < M;i++){ // Get a copy of Rand Matrix with only selected index
			for (j = 0;j < NumberFound;j++) {
				//printf("%d\n", i*NumberFound+ j);
				rand_Mat_Hat[i*NumberFound+ j] = Rand_Mat[i][indexSet[j]];
			}
		}

	
		transpose(M, NumberFound, rand_Mat_Hat, rand_Mat_Transpose);

		matMultiplication(NumberFound, M, 1, rand_Mat_Transpose, y, transpose_By_Y);

		matMultiplication(NumberFound, M, NumberFound, rand_Mat_Transpose, rand_Mat_Hat, rand_Mat_Squared);

		//printMatrix(NumberFound, NumberFound, rand_Mat_Squared);

		//int adj[NumberFound][NumberFound]; // To store adjoint of A[][] 
		/**
		//HERE
		float inv[NumberFound][NumberFound]; // To store inverse of A[][] 

		printMatrix(NumberFound, NumberFound, rand_Mat_Squared);
		inverse(NumberFound, rand_Mat_Squared, inv);
		//printMatrix(NumberFound, NumberFound, inv);
		matMultiplication(NumberFound, NumberFound, 1, inv, transpose_By_Y, inv_By_TransposeY);
		matMultiplication(M, NumberFound, 1, rand_Mat_Hat, inv_By_TransposeY, randMatHat_By_Inv);
		matSubtraction(M, 1, y, randMatHat_By_Inv, x_bar);
		magnitude(M, x_bar, x_bar_Mag);
		//printf("X bar magnitude is %f\n", x_bar_Mag[0]);
		x_hat[indexSet[NumberFound-1]] = x_bar_Mag[0];

		matMultiplication(M, N, 1, Rand_Mat, x_hat, residualX);
		//printMatrix(M, 1, residualX);
		matSubtraction(M, 1, y, residualX, r);
		//printMatrix(M, 1, r);
		**/


		//Initialize Q to be equal to input vector randMatSquared
		for (i = 0;i < NumberFound;i++){
			for (j = 0;j < NumberFound;j++) {
				//Initialize Q to be equal to A
				q[i][j] = rand_Mat_Squared[i][j];
				resultQR[i][j] = 0;
			}
		}
		
		qr(NumberFound, q, resultQR);


		transpose(NumberFound, NumberFound, q, qt);
				
		matMultiplication(NumberFound, NumberFound, 1, qt, transpose_By_Y, yQt);

		for(i=0;i<M;i++){
			x_hat_temp[i]=0;
		}

		backSubstitution(NumberFound, resultQR, yQt, x_hat_temp);
	

		for ( i = 0;i < NumberFound;i++){
			x_hat[indexSet[i]] = x_hat_temp[i]; //put the right value in the right positions
		}

		//printf("PRINTING FINDED INDEX iteration %d\n", ii);
		//print_int(finded_index, 1, N);
		

		float A_x_h[M];
		matMultiplication(M, N, 1, Rand_Mat, x_hat, A_x_h);

		matSubtraction(M, 1, y, A_x_h, r); //r = y - A*s_hat;
		
	}
	
	printf("Printing Approximation\n");
	for (i = 0;i <N;i=i+1) {
		printf("Index %d: ", i);
		printf("%.10f\n", x_hat[i]);
	}
	

	return 0; 
}



