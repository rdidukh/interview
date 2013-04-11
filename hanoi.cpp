#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

stack<int> L;
stack<int> M;
stack<int> R;

int n;

void print_hanoi()
{
    stack<int> l(L); 
    stack<int> m(M);
    stack<int> r(R);        
    //int _max = max(L.size(), max(M.size(), R.size()));
    int c = n;

/*    cout << "L.size() = " << L.size() << endl;
    cout << "M.size() = " << M.size() << endl;
    cout << "R.size() = " << R.size() << endl;
    cout << "max = " << _max << endl;
*/
    while(c > 0)
    {
        if(L.size() >= c) 
        {   
            printf("| %2i |", l.top());
            l.pop();
        }
        else
        {
            printf("|    |");
        }
        printf("%6s", "");      
            
        if(M.size() >= c) 
        {   
            printf("| %2i |", m.top());
            m.pop();
        }
        else
        {
            printf("|    |");
        }
        printf("%6s", "");

        if(R.size() >= c) 
        {   
            printf("| %2i |", r.top());
            r.pop();
        }
        else
        {
            printf("|    |");
        }
        printf("%6s\n", "");
        c--;
    }

    cout << "------------------------------" << endl << endl;
}

void die(const char* str)
{
    cout << str << endl;
    exit(EXIT_FAILURE);
}

void onemove(stack<int> & from, stack<int> & to)
{   
    if(from.empty()) die("Trying to move from empty stack.");
    int tmp = from.top();
    if(to.empty() || tmp < to.top())
    {
        to.push(tmp);
        from.pop();
    }   
    else if(tmp > to.top()) die("Trying to move on a bigger one.");
    
}

void move(stack<int> & from, stack<int> & to, stack<int> & tmp, int c)
{

    cout "" <<  << endl'

    if(c == 1)
    {
        onemove(from, to);
        print_hanoi();
        return;
    }

    move(from, tmp, to, c-1);
    move(from, to, tmp, 1);
    move(tmp, to, from, c-1);
}

void hanoi()
{
    move(L, R, M, n);
}

int main(int argc, char * argv[])
{
    n = atoi(argv[1]);

    for(int i = n; i > 0; i--)
    {
        L.push(i);
    }

    print_hanoi();
    hanoi();

}

