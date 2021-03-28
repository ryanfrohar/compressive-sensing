#include <stdio.h>
#include "stdio.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SIZE 16384
float MAX_RAND=7.0;

int main(){


	float phi[SIZE];
	int i;
	srand(time(NULL));

	FILE *f = fopen("phi.txt", "w");

	if (f == NULL){
    	printf("Error opening file!\n");
    	exit(1);
	}

	int randNum;
	//Make 6 random coeff out of N coeff in normalized vector >1 with range 2>x>24
	for (i = 0;i < SIZE;i++){
		phi[i] =  (float) rand()/(float)(RAND_MAX) * MAX_RAND;
	}
	for (i = 0;i <SIZE;i=i+1) {
		fprintf(f, "%f\n", phi[i]);
	}
	
	fclose(f);

	return 0;
}