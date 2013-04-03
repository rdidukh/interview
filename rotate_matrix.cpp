#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#define N 4

void print_matrix(int M[N][N])
{
    for(i = 0; i < N; i++)
    {
        if(i%N == 0) std::cout << std::endl;
        printf("%2i",M[i/N][i%N]);
    }
    std::cout << std::endl;
}

void rotate_matrix(int M[N][N])
{
    int i, tmp, tmp_c, tmp_r;

    tmp = 0;
    tmp_c = 0;
    tmp_r = 0;
        
    for(i = 0; i < N*N; i++)
    {
        int c = tmp_c;
        int r = tmp_r;

        tmp_c = c;
        tmp_r = N-r-1;
        tmp = M[N-r-1][c];
        M[N-r-1][c] = tmp;
    }

}

int main()
{
    int M[N][N];
    
    srand(time(NULL));

    for(i = 0; i < N; i++)
        M[i/N][i%N] = rand()%(N*N)+1;

    print_matrix(M);

    rotate_matrix(M);    

    print_matrix(M);
}

