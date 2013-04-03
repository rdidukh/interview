/*
    Reverse a given string.    
    reverse_string <string>
*/

#include <cstring>
#include <iostream>

int main(int argc, char* argv[])
{
    int len = strlen(argv[1]);

    char *buf = new char[len];
    
    int i;
    for(i = 0; i <= len/2; i++)
    {
        buf[i] = argv[1][len-i-1];
        buf[len-i-1] = argv[1][i];
    }

    std::cout << buf << std::endl;

    delete[] buf;

    return 0;
}

