#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(){
	
	FILE* fptr;
	fptr = fopen("unrolled_jamed.txt", "w");
	double t1, t2, time;
	int m=200, n=200, q=200;
	double a[m*n], b[n*q], c[m*q];

	//llena la primer matriz
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			a[(i*n)+j] = (double)j;
		}
	}
	//llena la segunda matriz
	for(int i = 0; i < n; i++){
		for(int j = 0; j < q; j++){
			b[(i*q)+j] = (double)2*j;
		}
	}
	//toma el tiempo del cronómetro (inicio)
	t1 = omp_get_wtime();

	//multiplicacion con metodo unrolled and jamed
	for(int j = 0; j < q; j+=2){
		for(int i = 0; i < m; i++){
			c[(i*q)+j] = 0;
			c[(i*q)+j+1] = 0;
			for(int k = 0; k < n; k++){
				c[(i*q)+j] += (a[(i*n)+k]*b[(k*q)+j]);
				c[(i*q)+j+1] += (a[(i*n)+k]*b[(k*q)+j+1]);
			}
		}
	}
	//toma el tiempo del cronómetro (fin)
	t2 = omp_get_wtime();
	time = t2 - t1; //tiempo que tomo la ejecucion
	printf("Total time = %f\n",time);
	
	//imprimie en archivo txt
	for(int i = 0; i < m; i++){
		for(int j = 0; j < q; j++){
			fprintf(fptr, "%f ", c[(i*q)+j]);
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
	return 0;
}


