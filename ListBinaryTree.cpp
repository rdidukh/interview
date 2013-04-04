#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <list>

template<class T>
class ListBinarySearchTree
{
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

    }

    unsigned max_depth()
    {
        max_depth(root, 1);
    }

    void print()
    {
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
    
    bst.insert(10);
    bst.insert(20);
    bst.insert(30);
    bst.insert(15);    
    bst.insert(40);
    bst.insert(50);

    bst.print();

//     std::cout << "depth = " << bst.max_depth() << std::endl;

    return 0;
}


