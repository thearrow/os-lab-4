//Jacob Klingler
//klinglej
//klingler.45@osu.edu
//OS Lab #4 (Multithreaded Matrix Multiplication)

//To compile, executethe command:
// gcc -O1 -Wall -o mult main.c -lpthread
//NOTE:('-O1' in the previous line is a capital letter 'o')
//NOTE:(Ignore the harmless gcc warnings)

//To run, execute the command: mult

//This program multiplies two matrices using 1-8 threads and reports timing

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>

#define M 1000
#define N 1200
#define P 500

int A[N][M], B[M][P], C1[N][P], C[N][P];
int num_threads = 1;

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
//multiply 'n-th chunk' of matrices C=A*B
    
    int chunk = (int)n;
    int start = (chunk*N)/num_threads;
    int end = ((chunk+1)*N)/num_threads;
    
    int i,j=0;
	for (i = start; i < end; i++)
	{
		for(j = 0; j < P; j++){
            C[i][j] = 0;
			int k=0;
			for (k = 0; k < M; k++){
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
    
    return 0;
}

int threadedMultiply(int n){
//perform C=A*B using n threads
    
    pthread_t* threads;
    threads = (pthread_t*) malloc(n*sizeof(pthread_t));
	pthread_attr_t p_attr;
	pthread_attr_init(&p_attr);
    num_threads = n;
	int i=0;
	for(i=0;i<n;i++){
        //create threads and pass 'chunk' number
		pthread_create(&threads[i],&p_attr,multiplyChunk,(void*)i);
	}
    
    for(i=0;i<n;i++){
        //wait for all threads to finish
        pthread_join(threads[i], NULL);
    }
    
    free(threads);
    return 0;
}

void printParts(){
//print sections of matrices C and C1 for visual comparison
    
    int i=0;
    printf("\tC:\t\t\tC1:\n");
    for (i=444; i<456; i++) {
        printf("\t%d\t\t%d\n",C[i][200],C1[i][200]);
    }
}

int main(void){
//perform matrix multiplication and timing
	struct timeval start, end;
    
	initMatrices();
	printf("Matrices Initialized!\n");
    printf("Threads\t\tSeconds\n");
    
    //perform + time single-threaded multiplication
	gettimeofday(&start, NULL);
	simpleMultiply(); //C1 = A*B
	gettimeofday(&end, NULL);	
	printf("\t1\t\t %lfs\n", ((end.tv_sec * 1000000 + end.tv_usec)
                              - (start.tv_sec * 1000000 + start.tv_usec))/1000000.0);
    
    //perform + time multi-threaded multiplication for 2-8 threads
    int i=2;
    for (i=2; i<=8; i++) {
        gettimeofday(&start, NULL);
        threadedMultiply(i);
        gettimeofday(&end, NULL);
        printf("\t%d\t\t %lfs\n", i, ((end.tv_sec * 1000000 + end.tv_usec)
                                  - (start.tv_sec * 1000000 + start.tv_usec))/1000000.0);
        
    //printParts();
    //uncomment to print a part of the matrices for visual comparison
        
        int r=compareMatrices();
        if(r==1)
            printf("\t\tNo errors detected!\n");
        else if (r==-1)
            printf("\t\t\t\tError Detected!\n");
    }
    
}