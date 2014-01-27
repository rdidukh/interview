#include "ListBinarySearchTree.cpp"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>

// static const int SIZE = 10;

void sorted_array_to_bst(int* array, ListBinarySearchTree<int> &bst, int left, int right)
{
    if(right <= left) throw std::string("FATAL: right <= left");

    int ind = (left+right)/2;
    bst.insert(array[ind]);  

//     if((right - left) == 1) return;
      
    if(left < ind)
        sorted_array_to_bst(array, bst, left, ind);   
    if(ind+1 < right)
        sorted_array_to_bst(array, bst, ind+1, right);   
}

int main()
{
    srand(time(NULL));

    ListBinarySearchTree<int> bst;
    
    int SIZE = rand()%8 + 8;

    int *A = new int[SIZE];
    
    A[0] = rand()%10+1;
    for(int i = 1; i < SIZE; i++)
        A[i] = rand()%5 + A[i-1] + 1;
    

    for(int i = 0; i < SIZE; i++)
        std::cout << A[i] << ", ";
    std::cout << std::endl;
    
    sorted_array_to_bst(A, bst, 0, SIZE);

    bst.print();

    delete[] A;

    return 0;
}


