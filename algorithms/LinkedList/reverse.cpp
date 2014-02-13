#include <iostream>
#include <string>

using namespace std;

struct LinkedList
{
    char data;
    LinkedList *next;
};

void printList(LinkedList * head)
{
    LinkedList* lst = head;         

    while(lst != NULL)
    {
        cout << lst->data;
        if(lst->next != NULL)
            cout << " - ";
        lst = lst->next;
    }
    cout << endl;

}

void reverseRec(LinkedList * head, LinkedList * prev)
{
    if(head == NULL) return;
    reverseRec(head->next, head);
    head->next = prev;
}

int main()
{
    string cmd;
    
    LinkedList *head = NULL;
    LinkedList *tail = NULL;    

    while(true)
    {
                  cout << "> ";
        cin >> cmd;

        if(cmd == "q") break;

        if(cmd == "i" || cmd == "insert")
        {
            char tmp;
            cin >> tmp;

            if(head == NULL)
            {
                head = new LinkedList();
                head->data = tmp;
                head->next = NULL;
                tail = head;
            }
            else
            {
                tail->next = new LinkedList();
                tail = tail->next;
                tail->data = tmp;
                tail->next = NULL;
                
            }
        }
        else if(cmd == "p" || cmd == "print")
        {
            printList(head);
        }
        else if(cmd == "reverse")
        {
            reverseRec(head, NULL);
            
            LinkedList* lst = head;  
            head = tail;
            tail = lst;
            
        }
        else
        {
            cout << "Unsupported command." << endl;
        }
        
        //istream& ignore (streamsize n = 1, int delim = EOF);
        cin.ignore(10, '\n');

    }

    
    //delete head;
}
