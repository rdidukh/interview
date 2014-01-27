#include <iostream>
#include "Heap.h"

using namespace std;

int main(int argc, char* argv[])
{

    Heap<int> heap(10);
        
    string cmd;

    while(1)
    {
        cout << "> ";
        cin >> cmd;
            
        if(cmd == "quit" || cmd == "q" || cmd == "exit") break;
        if(cmd == "p" || cmd == "print")
        {
            heap.print();
            continue;
        }
        if(cmd == "i" || cmd == "insert")
        {
            int value;
            cin >> value;
            heap.push(value);
            continue;
        }
        if(cmd == "m" || cmd == "max")
        {
            cout << heap.getmax() << endl;
            continue;
        }
        if(cmd == "pop")
        {
            cout << heap.pop() << endl;
            continue;
        }

    }

    return 0;
}
