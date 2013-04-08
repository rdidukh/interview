#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int size;

void quick_sort(int *array, int left, int right)
{
    int i;
    if(right-left <= 1) return;
    int m = rand()%(right-left) + left;
//    printf("(left, right, m) = (%i, %i, %i)\n", left, right, m);
    for(i = 0; i < size-1; i++)
        printf("%i, ", array[i]);
    printf("%i\n\n", array[i]);    
    
 
    
    if(right-left == 2)
    {
        if(array[left] > array[left+1])
        {
            int tmp = array[left];
            array[left] = array[left+1];
            array[left+1] = tmp;
        }
        return;
    }
   
    
    int l = left;
    int r = right-1;
    
    while(1)
    {
        printf("-- (l , r, m) = (%i, %i, %i)\n", l, r, m);
        while((l < m) && (array[l] < array[m])) l++;
        while((r > m) && (array[r] > array[m])) r--;;
        if(l == r) break;
        
        if((l < m) && (r > m))
        {
            if(array[l] != array[m])
            {
                int tmp = array[l];
                array[l] = array[r];
                array[r] = tmp;
                continue;
            }
            else
            {
                l++;
                r--;
                continue;
            }
        }
        
        if((l < m) && (r == m))
        {
            int tmp = array[l];
            array[l] = array[m-1];
            array[m-1] = array[m];
            array[m] = tmp;
            m--;
            r--;
            continue; 
        }
        
        if((r > m) && (l == m))
        {
            int tmp = array[r];
            array[r] = array[m+1];
            array[m+1] = array[m];
            array[m] = tmp;
            m++;
            l++;
            continue; 
        }
        
    }
    printf("++ (l , r, m) = (%i, %i, %i)\n", l, r, m);
    quick_sort(array, left, m);
    quick_sort(array, m+1, right);
    
}

int main(int argc, char* argv[])
{
    srand(time(NULL));

    size = atoi(argv[1]);

    int *A = (int*) malloc(size*sizeof(int));

    int i;
    for(i = 0; i < size; i++)
        A[i] = 10;//rand()%50;
    
    for(i = 0; i < size-1; i++)
        printf("%i, ", A[i]);
    printf("%i\n", A[i]);

    quick_sort(A, 0, size);

    for(i = 0; i < size-1; i++)
        printf("%i, ", A[i]);
    printf("%i\n", A[i]);

    free(A);

    return 0;
}

