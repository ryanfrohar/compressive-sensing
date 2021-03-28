#include <stdio.h>
#include "stdio.h"



int main(){
	printf("WE MADE IT");

	float Rand [6][25];
	float xsig [25];

	FILE *phi;
	phi = fopen("phi.dat", "r");
	for(int row = 0; row < 6; row++){
		for(int col = 0; col < 25; col++){
				fscanf(phi, "%f", Rand[row][col]); //Populate with random values from 0-9
		}
	}

	fclose(phi);
	FILE *myFile;
	myFile = fopen("inputSignal.dat", "r");
	for (int i = 0; i < 25; i++){
		fscanf(myFile, "%f", xsig[i]);
	}
	fclose(myFile);
	OMP(Rand,xsig);

}
