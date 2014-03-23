#include <iostream>
#include <string>
#include <vector>
using namespace std;

class KnuthMorrisPratt
{
    
    vector<int> V;

public:

    int search(const string & str, const string & pattern, unsigned offset)
    {
        int patlen = pattern.length();
        V.resize(patlen, 0);

        int ptr = 0;

        for(int i = 1; i < patlen; i++)
        {
            while((pattern[i] != pattern[ptr]) && (ptr > 0))
                ptr = V[ptr-1];
            
            if(pattern[i] == pattern[ptr]) ptr++;

            V[i] = ptr;
        }

        ptr = 0;
        int i;

        for(i = 0; i < str.length(); i++)
        {

            while((str[i] != pattern[ptr]) && (ptr > 0))
                ptr = V[ptr-1];

            cout << "str[" << i << "] <---> pat[" << ptr << "]" << endl;

            if(str[i] == pattern[ptr]) ptr++;

            if(ptr == patlen) break;            
        }        

        if(ptr < patlen) return -1;
        return i - patlen + 1;
    }
};

int main(int argc, char* argv[])
{
    KnuthMorrisPratt kmp;

    string str(argv[1]);
    string pat(argv[2]);

    cout << kmp.search(str, pat, 0) << endl;

    return 0;
}
