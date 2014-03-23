#include <iostream>
#include <string>
using namespace std;

template<class T>
class hash
{
  public:  

  unsigned operator()(const T & val)
  {
    return 0;
  }

};

template<>
class hash<int>
{
  public:
  unsigned operator()(const int & val)
  {
    return val;
  }

};

template<class Key, class Value, class Hash = hash<Key> >
class HashMap
{  
    
  struct Node
  {
    Key key;
    Value value;
    unsigned hash;
    Node * next;    

    Node(const Key& k, const Value& v, unsigned h, Node* n):
      key(k), value(v), hash(h), next(n) {}    
  };
 
  class iterator
  {
    friend class HashMap;
    unsigned index;   
    Node * node;
    
    iterator(unsigned i, Node* n): index(i), node(n) {}
    
    public:   
  
    void operator++()
    {     
      next();     
    }
   
    iterator& operator++(int)
    {
      next();
      return *this;
    }
   
    bool operator==(const iterator& rhs)
    {
      return (node == rhs.node);       
    }
    
    bool operator!=(const iterator& rhs)
    {
      return (node != rhs.node);
    }
    
    const Key& operator*()
    {
      if(node == NULL) return *((Key *)NULL);
      return node->key;
    }
    
    const Key& key()
    {
      return node->key;
    }
    
    Value& value()
    {
      return node->value;
    }
    
    void next()
    {
      if(node == NULL) 
        return;  
      else
        node = node->next;
        
      while(node == NULL && index < size)
      {
        node = nodes[index];
        index++;      
      }              
    }
    
  };
    
  Node ** nodes;
  unsigned size;
  unsigned count;
  Hash hasher;   

 public:
  HashMap()
  {
      size = 0;
      count = 0;
      nodes = NULL;
  }
 
  
  void set(const Key & key, const Value & value)  
  {  
     unsigned hash = calcHash(key); 
     Node* node = findNode(key, hash); 
     if(node == NULL)
     {
       if(count+1 >= size/4*3)       
         resize(max(4, 2*size));
       unsigned index = getIndex(hash);
    
       node = nodes[index];

       nodes[index] = new Node(key, value, hash, node);

      

       count++;
     }
     else
     {
       node->value = value;          
     }       

  }
 
  
  Value& get(const Key& key)
  {
    unsigned hash = calcHash(key); 
    unsigned index = getIndex(hash);  
    
    Node* node = findNode(hash, key); 
      
    if(node == NULL) throw "Not implemented";
      
    return node->value;
  }

  
  bool has(const Key& key)
  {
    unsigned hash = calcHash(key);    
    Node* node = findNode(key, hash); 
    return (node != NULL);
  }
 
  
  void remove(const Key& key)
  {
    unsigned hash = calcHash(key);    
    unsigned index = getIndex(hash);
    
    Node* node = nodes[index];     
    if(node == NULL) return; 
    
    if(node->key == key)
    {
      nodes[index] = node->next;
      delete node;
      count--;
      if(count < (size+1)/4) resize(size/2);
      return;  
    }
    
    Node* next = node->next;
    
    while(next != NULL)
    {   
      if(next->hash == hash && next->key == key)
      {
        node->next = next->next;
        delete next;
        count--;
        break;
      }
     
      node = next;
      next = next->next;
    }
    
  }

  
  void clear()
  {
    for(int i = 0; i < size; i++)
    {
      Node * node = nodes[i];
      
      while(node != NULL)
      {
        Node *tmp = node->next;
        delete node;
        node = tmp;
      }
      
      delete[] nodes;
    }
    
    size = 0;
    count = 0;
    nodes = NULL;
  }
 
  
  void resize(unsigned newsize)
  {
    if(newsize == 0)
    {
      clear();
      return;     
    }
    
    if(newsize == size) return;
    
    Node ** newnodes = new Node*[newsize]; // filled with NULLs

    for(int i = 0; i < newsize; i++)
      newnodes[i] = NULL;

    unsigned newcount = count;
       
    for(int i = 0; i < size; i++)
    {
      Node* node = nodes[i];
      
      while(node != NULL)
      {
        Node* tmp = node->next;
        
        unsigned index = getIndex(node->hash, newsize);        
        Node* next = newnodes[index];      
        newnodes[index] = node;
        node->next = next; 
              
        node = tmp;
      }
      
    }
    
    if(nodes != NULL)
      delete[] nodes;
    
    nodes = newnodes;
    size = newsize;   
  }
 
  iterator begin()
  {    
    Node* node = NULL;
    
    unsigned i = 0;
    
    while(node == NULL && i < size)
    {
      node = nodes[i];
      i++;
    }
    
    return iterator(i, node);
  }
  
  iterator end()
  {
    return iterator(size, NULL);     
  }

  
  void debug()
  {
    cout << "size = " << size << endl;
    cout << "count = " << count << endl;
    
    for(int i = 0; i < size; i++)
    {
      Node* node = nodes[i];
      cout << i << ": ";
      cout << "node = " << node << endl;
      while(node != NULL) 
      {
        cout << " (" << node->key << " -> " << node->value << ", " << node->hash << ")"; 
        node = node->next;
      }
      cout << endl;
    }
    
  }
  
 private:
  
  unsigned calcHash(const Key & key)
  {
    return hasher(key);
  }
  
  
  Node* findNode(const Key& key, unsigned hash)
  { 
    if(size == 0) return NULL;
    if(count == 0) return NULL;
    
    unsigned index = getIndex(hash);
    
    Node* node = nodes[index];
      
    while(node != NULL)
    {
      if(node->hash == hash && node->key == key) break;       
      node = node->next;
    }     
 
    return node;
  }
  
  unsigned getIndex(unsigned hash, unsigned limit = -1)
  {   
    if(limit == -1) limit = size;
    if(limit == 0) return 0;
    return hash % limit;
  }
  
  unsigned max(unsigned left, unsigned right)
  {
    if(left > right) return left;  
    return right;
  }

};




int main(int argc, char* argv[])
{
    HashMap<int, string> hashmap;
        
    string cmd;

    while(1)
    {
        cout << "> ";
        cin >> cmd;
            
        if(cmd == "quit" || cmd == "q" || cmd == "exit") break;
        if(cmd == "p" || cmd == "print")
        {
            hashmap.debug();
            continue;
        }
        if(cmd == "s" || cmd == "set")
        {
            int key;
            string value;
            cin >> key >> value;
            hashmap.set(key, value);
            continue;
        }
        if(cmd == "g" || cmd == "get")
        {
            int key;
            cin >> key;            
            cout << hashmap.get(key) << endl;
            continue;
        }
        if(cmd == "r" || cmd == "remove")
        {
            int key;
            cin >> key;            
            hashmap.remove(key);
            continue;
        }
    }

    return 0;
}

