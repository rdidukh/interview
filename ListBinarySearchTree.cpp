#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <list>
#include <string>


template<class T>
class ListBinarySearchTree
{

    typedef std::vector<std::list<T> > VectorList ;

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

    Node * find(const T & value)
    {
        if(root == NULL) return NULL;    
        
        Node * node = root;
        while(node != NULL)
        {
            if(node->value == value) return node;
            if(value > node->value)
            {
                node = node->right;
                continue;
            }
            if(value < node->value)
            {
                node = node->left;
                continue;
            }
        }
        
        return NULL;

    }

    Node * max(Node * _root)
    {
        if(_root == NULL) return NULL;
        Node * node = _root;
        while(node->right != NULL)
            node = node->right;
        return node;
    }

    Node * min(Node * _root)
    {
        if(_root == NULL) return NULL;
        Node * node = _root;
        while(node->left != NULL)
            node = node->left;
        return node;
    }

    Node * parent(Node * node)
    {
        Node * p = NULL;
        Node * n = root;
        while(n != node)
        {
            p = n;
            if(node->value > n->value)
            {
                n = n->right;
            }
            else if(node->value < n->value)
            {
                n = n->left;
            }
    
        }        

        return p;
    }

    Node * find_sum(const T& value, Node * start, Node * node, T sum)
    {
        if(node == NULL) return;
        
        sum += node->value;

        Node * right = find_sum(value, start, node->right, sum);
        Node * left  = find_sum(value, start, node->left, sum);

        if(node == start)
        {

        }

        if(sum == value)
        {
            return node;
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
    
    T next(const T& value)
    {
        Node * m;
        Node * node = find(value);
        if(node == NULL) return -123;
        
        if(node->right != NULL) 
        {
            m = min(node->right);
            return m->value;
        }
        
        m = parent(node);
        while(m->value < value) 
        { 
            m = parent(m); 
            if(m == NULL) return value;
        }
        return m->value;

    }

   

    VectorList find_sum(const T& value)
    {
        VectorList vl;
        std::vector<T> vec;        

        find_sum(value, root, vl, vec, -1);        
            
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

