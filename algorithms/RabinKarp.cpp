#include <string>
#include <cassert>
#include <iostream>

using namespace std;

class RabinKarpPatternMatch
{
    const unsigned base;
    const unsigned p;   

    unsigned hash(const string & str, unsigned offset, unsigned length)
    {
        unsigned result = 0;

        assert(str.length() >= offset + length);

        for(int i = offset; i < offset+length; i++)
        {
            result = (result * base) % p;
            result = (result + str[i]) % p;
        }

        return result;
    }

    unsigned rollhash(unsigned oldhash, unsigned basepow, char oldchar, char newchar)
    {
        assert(oldhash < p);
        assert(basepow < p);

     //   cout << "rollhash: oldhash = " << oldhash << ", basepow = " << basepow << ", oldchar = " << oldchar << ", newchar = " << newchar << endl;

        unsigned result = (oldhash + p - (oldchar*basepow)%p) % p;
        result = (result * base) % p;
        result = (result + newchar) % p;
        return result;
    }

    bool cmp(const string & pattern, const string & str, unsigned offset)
    {       
        assert(str.length() >= pattern.length() + offset);
        
        for(int i = 0; i < pattern.length(); i++)
            if(pattern[i] != str[offset + i]) return false;

        return true;
    }
    
    public:
    
    RabinKarpPatternMatch(): base(256), p(65521) {}

    int search(const string & str, const string & pattern, unsigned offset)
    {
       // cout << "search: str = \'" << str << "\', pattern = \'" << pattern << "\', offset = " << offset << endl; 

        if(str.length() < pattern.length() + offset) return -1;

        unsigned pathash = hash(pattern, 0, pattern.length());

     //   cout << "search: pathash = " << pathash << endl;

        unsigned basepow = 1;
        for(int i = 1; i < pattern.length(); i++)
            basepow = (basepow * base) % p;

        unsigned strhash = hash(str, offset, pattern.length());

       // cout << "search: strhash = " << strhash << endl;        

        if(strhash == pathash)
            if(cmp(pattern, str, offset)) return offset;

        int limit = str.length() - pattern.length() + 1;

        for(int i = offset+1; i < limit; i++)
        {
            strhash = rollhash(strhash, basepow, str[i-1], str[i-1+pattern.length()]);
         
          //  cout << "  i = " << i << ", strhash = " << strhash << ", pathash = " << pathash << endl;
   
            if(strhash == pathash)
                if(cmp(pattern, str, i)) return i;
        }


        return -1;
    }
    
    
};


int main(int argc, char* argv[])
{
    RabinKarpPatternMatch rk;

    int counter = 0;

    while(true)
    {

        int result = rk.search(string(argv[1]), string(argv[2]), counter);

        if(result == -1) break;

        cout << "main: result = " << result << endl;

        counter = result + 1;
    }

    return 0;
}
