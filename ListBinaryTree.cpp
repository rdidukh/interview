#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <list>
#include <string>


template<class T>
class ListBinarySearchTree
{
    int k;

    struct Node
    {
        T value;
        Node *left;
        Node *right;
        
    };
    
    Node* root;

    unsigned max_depth(Node *node, int i)
    {
        int left;
        int right;

        if(root == NULL) return 0;
            
        if(node->left != NULL) 
            left = max_depth(node->left, i+1);
        else
            left = i;

        if(node->right != NULL) 
            right = max_depth(node->right, i+1);
        else
            right = i;

        return right>left?(right):left;

    }

    T nth_max(Node *node, int n)
    {
/*        std::cout << "nth_max()" << std::endl;
        if(node)    
            std::cout << "value: " << node->value << std::endl;
        else
            std::cout << "NULL" << std::endl;
        std::cout << "n: " << n << std::endl;
        std::cout << "k: " << n << std::endl;
*/
        T max = 0;
    
        if(node == NULL)
            return 0;

        max = nth_max(node->right, n);
//        std::cout << std::endl;
//        std::cout << "max(rigth) = " << max << std::endl;
//        std::cout << "k = " << k << " --> " << k+1 << std::endl;
        k++;

        

        if(k == n)
        {
//            std::cout << "k == n" << std::endl;
            return node->value;
        }
        else if(k < n)
        {
//            std::cout << "k < n" << std::endl;
            max = nth_max(node->left, n);
//            std::cout << "max(left) = " << max << std::endl;
            return max;
        }
        else if(k > n)
        {
            return max;
        }

    }     

    public:

    ListBinarySearchTree(): root(NULL) {};

    

    void insert(const T & value)
    {
        Node * node = new Node();
        node->value = value;    
        node->left = NULL;
        node->right = NULL;
    
        if(root == NULL)
        {
            root = node;
            return;
        }

        Node *last = root;

        while(last != NULL)
            if(value > last->value)
            {
                if(last->right == NULL)
                {
                    last->right = node;
                    break;
                }

                last = last->right;
                
            }
            else if(value < last->value)
            {
                if(last->left == NULL)
                {
                    last->left = node;
                    break;
                }
                last = last->left;
            }
            else
            {
                return;
            }
    }

    void remove(const T& value)
    {
        bool right;
        if(root == NULL) return;
        Node * node = root;
        Node * parent = NULL;
        
        while(1)
        {
            if(node == NULL) return;
            if(value == node->value) break;
            parent = node;
            if(value > node->value) 
            {
                node = node->right;
                right = true;
                continue;
            }    
                
            if(value < node->value)
            {
                node = node->left;
                right = false;
                continue;
            }
        }
    
        
        if((node->left == NULL) && (node->right == NULL))
        {
            if(parent != NULL)
                if(right) parent->right = NULL; else parent->left = NULL;
            else
                root = NULL;
            delete node;
            return;
        }
        
        if(node->left == NULL)
        {
            if(parent != NULL)
                if(right) parent->right = node->right; else parent->left = node->right;
            else
                root = node->right;
            delete node;
            return;
        }
        
        if(node->right == NULL)
        {
            if(parent != NULL)
                if(right) parent->right = node->left; else parent->left = node->left;
            else
                root = node->left;
            delete node;
            return;
        }
        
        Node * min = node->right;
        while(min->left != NULL) min = min->left;
        
        T tmp = min->value;
        remove(tmp);
        node->value = tmp;
        
    }

    unsigned max_depth()
    {
        max_depth(root, 1);
    }


    T max(int n)
    {
        k = 0;
        return nth_max(root, n);
    }  
    

    void print()
    {
        if(root == NULL)
        {
            std::cout << "(empty)" << std::endl;
            return;
        }
    
        unsigned depth = max_depth();
        unsigned tab = (1 << depth) - 1;

        std::queue<Node *> q;
        std::list<Node *> l;    

        q.push(root);
        l.push_back(root);       

        int i;

        for(i = 0; i < (2 << (depth-2))-1; i++)        
        {
            Node *node = q.front();
            if(node == NULL)
            {
                l.push_back(NULL);
                l.push_back(NULL);
                q.push(NULL);
                q.push(NULL);
            }   
            else
            {
                l.push_back(node->left);
                l.push_back(node->right);
                q.push(node->left);
                q.push(node->right);
            }
            q.pop();
        }
    
        int cur_depth = 0;
        int counter = 0;

 
        for(i = 0; i < tab/2; i++)
            printf("  ");
    
        typedef typename std::list<Node *>::iterator NodeListIterator;
    
        for(NodeListIterator it = l.begin(); it != l.end(); ++it)
        {

            if(*it != NULL)
                printf("%2i", (*it)->value);
            else
                printf("**");

            for(i = 0; i < tab; i++)
                printf("  ");

            counter++;

            if(counter == (1 << (cur_depth)))
            {
                counter = 0;
                cur_depth++;
                std::cout << std::endl;
                tab /= 2;
                for(i = 0; i < tab/2; i++)
                    printf("  ");
            }

        }

    }

};


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
        bst.print();
    }
    
    return 0;
}


