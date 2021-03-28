#include <stdio.h>
#include "stdio.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(){

	float x[256];
	int i;
	srand(time(NULL));

	FILE *f = fopen("inputSignal.txt", "w");

	if (f == NULL){
    	printf("Error opening file!\n");
    	exit(1);
	}

	for (i = 0;i <256;i=i+1) {
		x[i] = 0;  //Create a normalized vector with values all <1
	}

	int randNum;
	//Make 6 random coeff out of N coeff in normalized vector >1 with range 2>x>24
	for (i = 0;i < 6;i++){
		randNum = (int) (rand() % 256);
		x[randNum] = (float)(rand() % 15);
		if(x[randNum] < 5.0){
			x[randNum] += 10.0;
		}
	}
	for (i = 0;i <256;i=i+1) {
		fprintf(f, "%f\n", x[i]);
	}
	
	fclose(f);

	return 0;
}