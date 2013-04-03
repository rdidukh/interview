/*
    Reverse a given string.    
    reverse_string <string>
*/

#include <cstring>
#include <iostream>

void reverse_1(const char *str, char *buffer)
{
    int len = strlen(str);
    
    int i;
    for(i = 0; i <= len/2; i++)
    {
        buffer[i] = str[len-i-1];
        buffer[len-i-1] = str[i];
    }
    buffer[len] = 0;
}

void reverse_2(char * str)
{
    if(*str == 0) return;

    char *end = str;
    while(*end) end++;
    end--;

    while(str < end)
    {
        char tmp = *str;
        *str++ = *end;
        *end-- = tmp;        
    }
}

int main(int argc, char* argv[])
{
    char buffer[512];

    reverse_1(argv[1], buffer);
    
    std::cout << "reverse_1: " << buffer << std::endl; 
    
    reverse_2(buffer);

    std::cout << "reverse_2: " << buffer << std::endl;

    return 0;
}

