/*
    Checks whether two strings are anagrams or not.
    check_anagrams <string 1> <string 2>
*/

#include <cstring>
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
    int i;

    if(strlen(argv[1]) != strlen(argv[2]))
    {
        std::cout << "NOT ANAGRAMS(LENGTH)" << std::endl;
        exit(0);
    }

    int * A = new int[256];
   
    memset(A, 0, sizeof(int)*256);

    char *s = argv[1];

    while(*s)
    {
        A[*s] += 1;
        s++;
    }
    s = argv[2];
    while(*s)
    {
        A[*s] -= 1;
        s++;
    }

    for(i = 0; i < 256; i++)
    {
        if(A[i] != 0) 
        {
            std::cout << "NOT ANAGRAMS" << std::endl;
            exit(0);
        }
    }
        
 
    std::cout << "ANAGRAMS" << std::endl;

    return 0;

}

