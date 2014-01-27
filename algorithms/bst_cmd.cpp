#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <list>
#include <string>
#include "ListBinarySearchTree.cpp"

int main()
{
    ListBinarySearchTree<int> bst;
    
    std::string cmd;
    
    while(1)
    {
        std::cout << ">";
        std::cin >> cmd;
        if(cmd == "q") break;
        if(cmd == "i")
        {
            int value;
            std::cin >> value;
            bst.insert(value);
        }
        if(cmd == "r")
        {
            int value;
            std::cin >> value;
            bst.remove(value);
        }
        if(cmd == "n")
        {
            int value;
            std::cin >> value;
            std::cout << "Next after " << value << " is " << bst.next(value) << std::endl;
        }
        bst.print();
    }
    
    return 0;
}


