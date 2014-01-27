#include <stdio.h>
#include <stdlib.h>

int len;

void die(const char *str)
{
    printf("%s\n", str);    
    exit(EXIT_FAILURE);

}

void msort(int *array, int left, int right, int *buffer)
{
/*
    printf("left = %i\n", left);
    printf("right = %i\n", right);
    printf("\n");
*/

    if(left > right) die("left >= right");                    
                  
    if(right-left <= 1) return;
           
    int middle = left+(right-left)/2;
           
    msort(array, left, middle, buffer);
    msort(array, middle, right, buffer);

    int i;
    for(i = left; i < right; i++)
        buffer[i] = array[i];
/*
    printf("left = %i\n", left);
    printf("middle = %i\n", middle);
    printf("right = %i\n", right);

    printf("pre  A: "); 
    for(i = 0; i < len; i++)
        printf("%i ", array[i]);
    printf("\n");

    printf("pre  B: "); 
    for(i = 0; i < len; i++)
        printf("%i ", array[i]);
    printf("\n");
*/

    int l = left;
    int r = middle;
    int cnt = l;

    while((l < middle) || (r < right))
    {    
//        printf("(l,r) = (%i, %i)\n", l, r);
//        usleep(100000);

        if(l == middle)
        {
            array[cnt] = buffer[r];
            r++;
            cnt++;
        }
        else if(r == right)
        {
            array[cnt] = buffer[l];
            l++;
            cnt++;
        }
        else if(buffer[l] <= buffer[r])
        {
            array[cnt] = buffer[l];
            l++;
            cnt++;
        }
        else if(buffer[r] <= buffer[l])
        {
            array[cnt] = buffer[r];
            r++;
            cnt++;
        }
        
    }
    
/*   
    printf("post A: "); 
    for(i = 0; i < len; i++)
        printf("%i ", array[i]);
    printf("\n\n");
*/

}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int *A;
    int *B;
    
    /*int*/ len = atoi(argv[1]);

    A = (int *)calloc(sizeof(int), len);
    B = (int *)calloc(sizeof(int), len);

    int i;
    for(i = 0; i < len; i++)
    {
        A[i] = rand()%20 + 1;
        printf("%i ", A[i]);
    }
    printf("\n");

    msort(A, 0, len, B);

    for(i = 0; i < len; i++)
        printf("%i ", A[i]);
    printf("\n");

    free(A);
    free(B);

}


