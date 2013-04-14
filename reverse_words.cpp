#include <cstring>
#include <iostream>

using namespace std;

void reverse_str(char * start, char *end)
{
    end--;
    while(start < end)
    {
        char tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end++;
    }
}

void reverse_words_1(const char *str, char * buffer)
{
    while(*str == ' ') str++;
    if(*str == 0) { buffer[0] = 0; return;}

    const char *end = str;
    
    while(*end) end++;
    end--;
    while(*end == ' ') end--;
    end++;
    
    const char *start = end;
    start--;
    int cnt = 0;
    
    while(1)
    {    
        while((*start != ' ') && (start != str)) start--;
        if(start == str) break; 
        start++;
      
        for(const char *p = start; p < end; p++)
            buffer[cnt++] = *p; 
         
        start--; 
         
        buffer[cnt++] = ' '; 
         
        while((*start == ' ') && (start != str)) start--;
        end = start+1; 
    }    

    for(const char *p = start; p < end; p++)
        buffer[cnt++] = *p; 
    
    buffer[cnt] = 0;
    
}

int main(int argc, char* argv[])
{

    char * str = argv[1];
  
    int len = strlen(str);
    
    char * buf = new char[len]; 
        
    reverse_words_1(argv[1], buf);

    cout << buf << endl;

    delete buf;

    return 0;
}

