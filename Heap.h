#include <iostream>
#include <string>

using namespace std;

template<class T>
class Heap
{
    unsigned max;
    unsigned size;
    
    T* A;
    
    void bubble_up(unsigned index)
    {
        unsigned i = index;
        if(i == 0) return;
        int p = (i-1)/2;
        if(A[i] < A[p])
        {
            T tmp = A[i];   
            A[i] = A[p];
            A[p] = tmp;
            bubble_up(p);
        }      
    }

    void bubble_down(unsigned index)
    {
        unsigned i = index;

        int c = min_child(i);

        if(c == -1) return;

        if(A[i] > A[c])
        {
            T tmp = A[i];
            A[i] = A[c];
            A[c] = tmp;
            bubble_down(c);
        }   
    }

    int min_child(int index)
    {
        unsigned i = index;
        unsigned l = 2*i + 1;
        unsigned r = 2*i + 2;

        if(l >= size) return -1;

        if(r >= size) return l;

        if(A[l] < A[r]) 
            return l;
        else
            return r;
    }

    public:
    
    Heap(const unsigned max_size)
    {
        size = 0;
        max = max_size; 
        A = new T[max];
    }

    void push(const T& val)
    {
        if(size == max) throw string("Trying to push in full heap.");
        A[size] = val;
        bubble_up(size);
        size++;
    }

    T getmax()
    {
        if(size == 0) throw string("Trying to get max from empty heap.");
        return A[0];        
    }

    T pop()
    {
        if(size == 0) throw string("Trying to pop from empty heap.");
        
        T ret = A[0];

        A[0] = A[size-1];

        size--;

        bubble_down(0);
            
        return ret;    
    }

    void print()
    {
        if(size == 0)
        {
            cout << "(empty)" << endl;
            return;
        }
            
        for(int i = 0; i < size; i++)
            cout << A[i] << " ";
        cout << endl;        
        

    }

    ~Heap()
    {
        delete[] A;
    }

};

