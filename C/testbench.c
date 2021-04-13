

#include <stdio.h>
#include "stdio.h"
#include "OMP.h"
#include "ap_cint.h"

int main(){

	int xsig[N];
	int compressedXSig [M];
	int reconstructedX [N];
	float randy[M][N];


	FILE *myFile;
	myFile = fopen("compressed.txt", "r");
	for (int i = 0; i < M; i++){
		fscanf(myFile, "%d", &compressedXSig[i]);

	}
	fclose(myFile);

	FILE *myFile2;
	myFile2 = fopen("samples.txt", "r");
	for (int z = 0; z < N; z++){
		fscanf(myFile2, "%d", &xsig[z]);
	}
	fclose(myFile2);

	FILE *myFile3;
	myFile3 = fopen("phi.txt", "r");
	for (int ro = 0; ro < M; ro++){
		for(int co=0; co<N; co++){
			fscanf(myFile3, "%f", &randy[ro][co]);
		}
	}
	fclose(myFile3);

	//Compresses original signal to an undersampled version
	//compressor(xsig, compressedXSig, Rand);

	//OMP Algorithm takes the compressed signal and by using the random matrix it returns an approximation of the original signal in reconstructedX
	OMP(randy, compressedXSig, reconstructedX);

	printf("Printing X AND Approximation\n");
	for(int j = 0;j <N;j=j+1) {
		printf("Index %d: (Original) %d (Approximated) %d\n", j, xsig[j], reconstructedX[j]);
	}
	signalToNoise(N, xsig,reconstructedX);
	return 0;

}
