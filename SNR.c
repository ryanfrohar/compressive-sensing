/**

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