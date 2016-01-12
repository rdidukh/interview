#include <string>
#include <vector>
using namespace std;

class Solution
{
    int kmp(const string &text, int start, const string & pattern)
    {
        int n = pattern.length();
        if(n == 0) return start;
        vector<int> pi(n, 0);
        int p = 0;
        for(int i = 1; i < n; i++)
        {
            while(p > 0 && pattern[p] != pattern[i] && 
                 pattern[p] != '.' && pattern[i] != '.')
                p = pi[p-1];
            if(pattern[p] == pattern[i] || pattern[p] == '.' || pattern[i] == '.')
                p++;
            pi[i] = p;
        }   
    
        p = 0;
        
        int len = text.length();
        for(int i = 0; i < len; i++)
        {
            while(p > 0 && pattern[p] != text[i] && pattern[p] != '.')
                p = pi[p-1];
            if(pattern[p] == text[i] || pattern[p] == '.')
                p++;
            
            if(p == n)
            {
                 return 1+i-n; 
            }
        }
        
        return -1;
    }
    
public:
    bool isMatch(string s, string p)
    {
        int n = s.length();
        int left = -1;
        vector<string> pats;
        
        for(int i = 0; i < p.length(); i++)
        {
            if(p[i] == '*')
            {
                if(i > left+1)
                    pats.push_back(p.substr(left+1, i-left-1));
                left = i;
            }
        }
        
        if(n > left+1)
            pats.push_back(p.substr(left+1, p.length()-left-1));
        
        int first = 0;
        if(pats.size() > 1 && s[0] != '*')
            first = 1;
        
        if(p.back() == '*')
            pats.push_back("");
        
        int size = pats.size();
        
        int pos = 0;
        
        if(first == 1)
        {
            int tmp = kmp(s, 0, pats[0]);
            if(tmp != 0) return false;
            pos = pats[0].length();
        }
        
        for(int i = first; i < size-1; i++)
        {
            int tmp = kmp(s, pos, pats[i]);
            if(tmp == -1)
                return false;
            pos = tmp+pats[i].size();
        }
        
        bool result = true;
        
        if(size == 1)
        {
            result = s == pats[0];
        }
        else
        {
            int len = pats.back().length();
            result = pats.back() == s.substr(n-len, len);
        }
        
        return result;
    }
};

#include "test.h"

int main()
{
  Solution sol;
  ASSERT_TRUE(sol.isMatch("hello", "*"));
  return 0;
}
