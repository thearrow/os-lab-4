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
#include <pthread.h>

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

void *multiplyChunk(int n){
    return NULL;
}

void threadedMultiply(int n){
	//create threads
	pthread_t p_tid;
	pthread_attr_t p_attr;
	pthread_attr_init(&p_attr);
	int i=0;
	while(i < n){
		pthread_create(&p_tid,&p_attr,multiplyChunk(i),NULL);
		i++;
	}
}

int main(void)
{
	struct timeval start, end;
    
	initMatrices();
	printf("Matrices Initialized!\n");
    printf("Threads\t\tSeconds\n");
    
	gettimeofday(&start, NULL);
	simpleMultiply();
	gettimeofday(&end, NULL);
	
	printf("\t1\t\t %lfs\n", ((end.tv_sec * 1000000 + end.tv_usec)
                              - (start.tv_sec * 1000000 + start.tv_usec))/1000000.0);
    
    int i=2;
    for (i=2; i<=6; i++) {
        gettimeofday(&start, NULL);
        threadedMultiply(i);
        gettimeofday(&end, NULL);
        
        printf("\t%d\t\t %lfs\n", i, ((end.tv_sec * 1000000 + end.tv_usec)
                                  - (start.tv_sec * 1000000 + start.tv_usec))/1000000.0);
    }
    
}