//Jacob Klingler
//klinglej
//klingler.45@osu.edu
//OS Lab #4 (Multithreaded Matrix Multiplication)

//To compile, execute: gcc main.c
//To run the shell, execute: a.out

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define M 1000
#define N 1200
#define P 500

int A[N][M], B[M][P], C1[N][P], C[N][P];

void initMatrices(){
	int i,j=0;
    
	//init A
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			A[i][j] = i+j;
		}
	}
    
	//init B
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < P; j++)
		{
			B[i][j] = j;
		}
	}
}

void simpleMultiply(){
	int i,j=0;
    
	//perform multiplication C1 = A * B
	for (i = 0; i < N; i++)
	{
		for(j = 0; j < P; j++){
			C1[i][j] = 0;
			int k=0;
			for (k = 0; k < M; k++){
				C1[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

void threadedMultiply(int n){
	printf("%d",n);
}

int main(void)
{
	struct timeval start, end;
	printf("Hello!\n");
    
	initMatrices();
    
	printf("Matrices Initialized!\n");
    
	gettimeofday(&start, NULL);
	simpleMultiply();
	gettimeofday(&end, NULL);
    
	printf("Threads\t\tSeconds\n");
	printf("\t1\t\t %lfs\n", ((end.tv_sec * 1000000 + end.tv_usec)
                              - (start.tv_sec * 1000000 + start.tv_usec))/1000000.0);
}