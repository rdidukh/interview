#include <cstring>
#include <iostream>

void replace_dup_chars(char * str)
{
    char *s = str;
    char *p;    
    bool dup = false;

    while(*s)
    {
        p = s+1;
        
        dup = false;

        while(*p)
        {
            if(*p == *s)
            {
                dup = true;
                *p = '_';
            }
            
            p++;        
        }

        if(dup) *s = '_';
        s++;    
    
    }

}

void remove_dup_chars(char * str)
{
    char *s;
    char *p;    
    bool dup = false;

    while(*str)
    {
        p = str+1;
        
        dup = false;

        while(*p)
        {
            if(*p == *str)
            {
                dup = true;
                s = p;
                while(*s)
                {
                    *s = *(s+1);
                    s++;
                }
                p--;
            }
            
            p++;        
        }

        if(dup)
        {
            s = str;
            while(*s)
            {
                *s = *(s+1);
                s++;
            }
            str--;
        }

        str++;    
    
    }

}



int main(int argc, char *argv[])
{
    char *str = new char[strlen(argv[1])];

    strcpy(str, argv[1]);
    replace_dup_chars(str);    
    std::cout << str << std::endl;

    strcpy(str, argv[1]);
    remove_dup_chars(str);    
    std::cout << str << std::endl;

    delete[] str;

    return 0;
}

