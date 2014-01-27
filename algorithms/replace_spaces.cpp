#include <iostream>
#include <cstring>

void replace_spaces_buffer(const char *str, char * buffer)
{
    const char *s = str;
    char *b = buffer;
    int spaces = 0;
    while(*s)
    {
        if(*s == ' ')
        {
            *b++ = '%';
            *b++ = '2';
            *b++ = '0';
        }
        else
        {
            *b++ = *s;
        }
        s++;
    }  

    *b = 0;

}

void replace_spaces(char *str)
{

    char *end = str;

    while(*end++);

    while(*str)
    {
        if(*str == ' ')
        {
            end += 2;
            char *s = end;
            while(s > str+2) 
            {
                *s = *(s-2);
                s--;
            }
            *str++ = '%';
            *str++ = '2';
            *str = '0';
        }
        str++;
    }

}

int main(int argc, char * argv[])
{
    char buffer[256];   
    
    replace_spaces_buffer(argv[1], buffer);

    std::cout << "replace_spaces_buffer: " << buffer << std::endl;

    memset(buffer, 0, 256);
    strcpy(buffer, argv[1]);

    replace_spaces(buffer);

    std::cout << "replace_spaces: " << buffer << std::endl;
}


