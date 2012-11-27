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
//initialize matrices to specified values
    
	int i,j=0;
	//init A
	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
			A[i][j] = i+j;
    
	//init B
	for (i = 0; i < M; i++)
		for (j = 0; j < P; j++)
			B[i][j] = j;
    
    //init c
    for (i = 0; i < N; i++)
		for (j = 0; j < P; j++)
			C[i][j] = -1;
}

void simpleMultiply(){
//perform multiplication C1 = A * B
    
	int i,j=0;
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

int compareMatrices(){
//compare matrices C1 and C, return 1 if they are equal, -1 otherwise
    
    int i,j=0;
	for (i = 0; i < N; i++)
	{
		for(j = 0; j < P; j++){
            if(C[i][j] != C1[i][j]){
                return -1;
            }
        }
    }    
    
    return 1;
}

void *multiplyChunk(void* n){
    
    int chunk = (int)n;
    
    return 0;
}

int threadedMultiply(int n){
//perform C=A*B using n threads
    
    pthread_t* threads;
    threads = (pthread_t*) malloc(n*sizeof(pthread_t));
	pthread_attr_t p_attr;
	pthread_attr_init(&p_attr);
	int i=0;
	while(i < n){
		pthread_create(&threads[i],&p_attr,multiplyChunk,(void*)i);
        pthread_join(threads[i], NULL);
		i++;
	}
    
    free(threads);
    return 0;
}

int main(void){
//==================================
	struct timeval start, end;
    
	initMatrices();
	printf("Matrices Initialized!\n");
    printf("Threads\t\tSeconds\n");
    
	gettimeofday(&start, NULL);
	simpleMultiply(); //C1 = A*B
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
        
        int r=compareMatrices();
        if(r==1)
            printf("\t\tNo errors detected!\n");
        else if (r==-1)
            printf("\t\t\t\tError Detected!\n");
    }
    
}