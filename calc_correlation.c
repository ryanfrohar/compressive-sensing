#include <stdio.h>
#include <math.h>
/*
	Used to calculate the optimization problem, needs the norm and inner multiplaction of
	columns to find max between gaussian random matrix and residual vector


*/

void main(){

}

void calc_correlation(int N,int correlation[N],int norms[N],float inner_sum[N]){
	for(int i = 0; i<N; i++){
		correlation[i] = fabs(inner_sum[i]/norms[i]);
	}
}
