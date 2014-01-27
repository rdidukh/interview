#include <cstdlib>
#include <iostream>
#include <list>
#include <stdexcept>
template <typename T>
class LinkedList
{   

    private: 

    struct Item
    {
        Item *next;
        T data;     
   
    };

    Item *first;
    int _size;

    public:

    class iterator
    {
        Item * item;

        iterator(Item * _item)
        {
            item = _item;
        }
     
        public:

        friend class LinkedList;

        iterator() {};

        iterator(const iterator& rhs) 
        {
            item = rhs.item;
        };

        bool operator==(const iterator & rhs)
        {
            return (item == rhs.item);
        } 
   
        bool operator!=(const iterator & rhs)
        {
            return (item != rhs.item);
        }

        iterator & operator++()
        {
            item = item->next;
            return *this;
        }

        iterator & operator++(int)
        {
            item = item->next;
            return *this;
        }

        T & operator*()
        {
            return item->data;
        }

        T & operator->()
        {
            return item->data;
        }

    };

    LinkedList()
    {
        _size = 0;
        first = NULL;
    }        

    unsigned size()
    {
        return _size;
    }

    bool empty()
    {
        return (_size == 0);
    }

    T& back()
    {
        if(empty()) throw std::logic_error("LinkedList::back() called on empty container.");

        Item * last = first;
        while(last->next != NULL) last = last->next;

        return last->data;
    }

    const T& back() const
    {
        if(empty()) throw std::logic_error("LinkedList::back() called on empty container.");

        Item * last = first;
        while(last->next != NULL) last = last->next;

        return last->data;
    }

    void push_back(const T& obj)
    {
        Item * last = first;
        Item * item = new Item();
        item->next = NULL;
        item->data = obj;

        if(last == NULL)
        {
            first = item;
        }    
        else
        {
            while(last->next != NULL) last = last->next;
            last->next = item;
        }
        _size++;
    }

    void pop_back()
    {
        if(empty()) throw std::logic_error("LinkedList::pop_back() called on empty container.");

        Item * last = first;
        Item * before_last = NULL;
        while(last->next != NULL)
        {
            before_last = last;
            last = last->next;
        }

        if(first == last) 
            first = NULL;
        else
            before_last->next = NULL;    
        
        delete last;
        
        _size--;
        
    }

    T& front()
    {
        if(empty()) throw std::logic_error("LinkedList::front() called on empty container.");
        return first->data;
    }

    const T& front() const
    {
        if(empty()) throw std::logic_error("LinkedList::front() called on empty container.");
        return first->data;
    }

    void push_front(const T& obj)
    {
        Item * item = new Item();
        item->next = first;
        item->data = obj;
        first = item;
        _size++;
    }

    void pop_front()
    {
        if(empty()) throw std::logic_error("LinkedList::pop_front() called on empty container.");
        Item * old_first = first;
        first = first->next;
        delete old_first;
        _size--;
    }

    iterator begin()
    {
        return LinkedList::iterator(first);
    }

    iterator end()
    {
        return iterator(NULL);
    }

    iterator insert (iterator position, const T& obj)
    {  
        Item * before_pos = first; 
        if(position.item != first)
            while(before_pos->next != position.item) before_pos = before_pos->next;

        Item * item = new Item();
        item->data = obj;
        item->next = position.item; 
        if(position.item != first)
            before_pos->next = item;
        else
            first = item;
        _size++;

        return iterator(item);

    }

    iterator erase (iterator position)
    {
        if(empty()) throw std::logic_error("LinkedList::erase() called on empty container.");
        if(position.item == NULL) throw std::logic_error("LinkedList::erase() called for end iterator.");

    }

    void test()
    {
        if(first == NULL)
        {
            std::cout << "[test] empty!" << std::endl;
            return;
        }

        Item* item = first;

        while(item != NULL)
        {
            std::cout << item->data << std::endl;
            item = item->next;
        }

    }

};

int main()
{

    LinkedList<int> lst;
    lst.push_back(5);
    lst.push_back(6);
    lst.push_back(7);

    LinkedList<int>::iterator it = lst.begin();

    lst.insert(it, 8);
    it = lst.end();
    lst.insert(it, 9);
    lst.insert(it, 10);
    it = lst.begin();
    lst.insert(it, 11);

    lst.erase(lst.begin());

    for(it = lst.begin(); it != lst.end(); it++)
    {
        std::cout << ":" << *it << std::endl;
    }

    

}
