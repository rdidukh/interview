#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cnt;

int min(int a, int b)
{
	if(a < b) 
		return a;
	return b;
}

int *M;
int l1;
int l2;

int D(char *first, int len1, char* second, int len2)
{
	cnt++;
	printf("cnt = %i\n", cnt);
	//printf("(%i, %i)\n", len1, len2);

	//printf("M[%i, %i] = %i\n", len1, len2, M[len1*l2 + len2]);
	if(M[len1*l2 + len2] != -1) return M[len1*l2 + len2];

	int res1, res2, res3;
		
	if((len1 == 0) && (len2 == 0)) return 0;	
		
	if((len1 > 0) && (len2 == 0)) return len1;
	
	if((len1 == 0) && (len2 > 0)) return len2;
		

	res1 = 1 + D(first, len1 - 1, second, len2);
	
	res2 = 1 + D(first, len1, second, len2 - 1);
					
	if(first[len1-1] == second[len2-1])
		res3 = D(first, len1-1, second, len2 - 1);		
	else
		res3 = 1 + D(first, len1-1, second, len2 - 1);		
		
	M[len1*l2 + len2] = min(min(res1, res2), res3);	
	return M[len1*l2 + len2];
		
}

int main(int argc, char *argv[])
{

	char* first = argv[1];
	char* second = argv[2];
	cnt = 0;

	l1 = strlen(first);
	l2 = strlen(second);

	M = (int *)calloc(sizeof(int), (l1+1)*(l2+1));
	

	int i;
	for(i = 0; i < (l1+1)*(l2+1); i++)
		M[i] = -1;

	//printf("M[%i, %i] = %i\n", l1, l2, M[l1*l2 + l2]);

	printf("Distance = %i\n", D(first, l1, second, l2));

	free(M);

	return 0;
}
