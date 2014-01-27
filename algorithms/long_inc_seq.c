#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{

	int i,j;

	if(argc != 2)
	{
		
		exit(EXIT_FAILURE);
	}

	int N = atoi(argv[1]);

	srand(time(NULL));

	int *A = (int *)calloc(sizeof(int), N);

	for(i = 0; i < N; i++)
	{
		A[i] = rand()%20;
		printf("%2d ", A[i]);
	}
	printf("\n");

	int *B = (int *)calloc(sizeof(int), N);
	
	for(i = 0; i < N; i++)
	{
		B[i] = 1;
		
		for(j = 0; j < i; j++)
		{
			if((A[i] > A[j]) && (B[i] <= B[j]))
				B[i] = B[j] + 1;
		}
		
	}	
	
	for(i = 0; i < N; i++)
	{
		printf("%2d ", B[i]);
	}
	printf("\n");


	free(A);
	free(B);

	return 0;
}
