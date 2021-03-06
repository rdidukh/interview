/*
    Checks whether input string contains unique characters or not.
    unique_chars <string>
*/

#include <map>
#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;

bool unique_chars_map(const char *str)
{
    const char *p = str;

    map<char, int> charmap;

    while(*p != 0)
        if(charmap.count(*p) == 0)
        {
            charmap[*p] = 1;
            p++;
        }
        else
            return false;

    return true;
}

bool unique_chars_array(const char* str)
{
    char *array = new char[256];

    memset(array, 0, 256*sizeof(char));
    int i;
    for(i = 0; i < strlen(str); i++)
    {
        if(array[str[i]] > 0) return false;
        array[str[i]]++;
    }
    
    delete[] array;

    return true;

}

bool unique_chars_brute(const char *str)
{
    const char *p = str;
    while(*p != 0)
    {
        const char *s = p;
        while(*s != 0)
        {
            s++;
            if(*s == *p) return false;
        }
        p++;
    }
    
    return true;
}

bool unique_chars_sort(const char * str)
{
    int i, j;

    char *buf = new char[strlen(str)];

    strcpy(buf, str);

    // selection sort:
    int len = strlen(buf);
    for(i = 0; i < len; i++)
    {
        int min = buf[i];
        int min_ind = i;
        for(j = i+1; j < len; j++)
            if(buf[j] < min)
            {   
                min = buf[j];
                min_ind = j;
            }

        char temp = buf[i];
        buf[i] = min;   
        buf[min_ind] = temp;
    }

    for(i = 0; i < len; i++)
        if(buf[i] == buf[i+1]) 
            {
                delete[] buf;
                return false;
            }
    
    delete[] buf;    
    return true;

}

int main(int argc, char* argv[])
{
    if(unique_chars_map(argv[1]))
        std::cout << "unique_chars_map: TRUE" << std::endl;   
    else
        std::cout << "unique_chars_map: FALSE" << std::endl;  

    if(unique_chars_brute(argv[1]))
        std::cout << "unique_chars_brute: TRUE" << std::endl;   
    else
        std::cout << "unique_chars_brute: FALSE" << std::endl;  

    if(unique_chars_sort(argv[1]))
        std::cout << "unique_chars_sort: TRUE" << std::endl;   
    else
        std::cout << "unique_chars_sort: FALSE" << std::endl;  

    if(unique_chars_array(argv[1]))
        std::cout << "unique_chars_array: TRUE" << std::endl;   
    else
        std::cout << "unique_chars_array: FALSE" << std::endl;  

    return 0;
}
