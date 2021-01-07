/**

Function to return inner product of a specific column of a matrix and a row vector.

matrix: 2x2 matrix containing float values. (float)
vector: 2x1 vector containing float values. (float)
matrixRows: Number of rows in the matrix being used. (int)
matrixColumns: Number of columns in the matrix being used. Same as the vector size. (int)
mulColumn: Index of the column being multiplied in the matrix. (int)

**/


float innerColMul_N(float matrix, float vector, int matrixRows, int matrixColumns, int mulColumn)
{
	float total = 0;  // Used to store the total product value of the multiplication
	float matrixIndexedElement = matrix + mulColumn;
	
	for(int i=0; i<M ; i++) {
		total = total + ((matrixIndexedElement + i*matrixColumns) * (vector + i));
	}
	
	return total;
}



/**

How I thought this would/should work

**/

float differentInnerColMul_N(float matrix, float vector, int matrixRows, int matrixColumns, int mulColumn)
{
	float total = 0;  // Used to store the total product value of the multiplication
	
	// Loop to multiply all elements of the matrix's selected column by the vector's elements
	for(int i=0; i<M ; i++) {
		total = total + (matrix[i][mulColumn] * vector[i]);
	}
	
	return total;
}