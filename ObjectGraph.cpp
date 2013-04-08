#include <list>
#include <queue>
#include <stack>
#include <utility>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <map>

using namespace std;

const unsigned MAX_CMD_LENGTH = 256;

template <typename T, typename W>
class ListWeightedGraph
{
    class Vertex;
    typedef list<pair<Vertex *, W> > ListPair;
    struct Vertex
    {
        ListPair V;  /* neighbours */
        T value;                     /* value */
    };
    
    typedef list<Vertex *> List;
    List V;

    //ListGraph();

    Vertex* find(const T& value)
    {    
        for(typename List::iterator it = V.begin(); it != V.end(); it++)
            if((*it)->value == value) return (*it);
        
        return NULL;
    }
    
    public:
    
    void insert(const T& value)
    {
        if(find(value) != NULL) return;
        Vertex *v = new Vertex();
        v->value = value;
        V.push_back(v);
    }
    
    /* Insert edge with weight 'w' from 'v1' to 'v2'. */
    void insert(const T& v1, const T& v2, const W& w)
    {
        Vertex *from = find(v1);     
        Vertex *to = find(v2);
        
        if(from == NULL || to == NULL) return;
        
        from->V.push_back(make_pair<Vertex *, W>(to, w));
    }
    
    void BFS(const T& value)
    {
    
        Vertex * start = find(value);
        if(start == NULL) return;
    
        static const int UNDISCOVERED = 0;
        static const int DISCOVERED = 1;
        static const int PROCESSED = 2;

    
        map<Vertex *, int> status;
        map<Vertex *, Vertex *> parent;
    
        for(typename List::iterator it = V.begin(); it != V.end(); it++)
            status[*it] = UNDISCOVERED;
        
        queue<Vertex *> q;
        q.push(start);
        status[start] = DISCOVERED;
        parent[start] = NULL;
        
        while(!q.empty())
        {
            Vertex *v = q.front();    
            q.pop();
           
            status[v] = PROCESSED;
        
            cout << v->value;
        
            for(typename ListPair::iterator it = v->V.begin(); it != v->V.end(); it++)
            {
                if(status[it->first] == UNDISCOVERED)
                {
                    status[it->first] = DISCOVERED;
                    parent[it->first] = v;    
                    q.push(it->first);
                }
                
            }
                  
            if(!q.empty()) cout << ", ";     
                    
        }
    
        cout << endl;
    }
    
    void DFS(const T& value)
    {
    
        Vertex * start = find(value);
        if(start == NULL) return;
    
        static const int UNDISCOVERED = 0;
        static const int DISCOVERED = 1;
        static const int PROCESSED = 2;

    
        map<Vertex *, int> status;
        map<Vertex *, Vertex *> parent;
    
        for(typename List::iterator it = V.begin(); it != V.end(); it++)
            status[*it] = UNDISCOVERED;
        
        stack<Vertex *> q;
        q.push(start);
        status[start] = DISCOVERED;
        parent[start] = NULL;
        
        while(!q.empty())
        {
            Vertex *v = q.top();    
            q.pop();
           
            status[v] = PROCESSED;
        
            cout << v->value;
        
            for(typename ListPair::iterator it = v->V.begin(); it != v->V.end(); it++)
            {
                if(status[it->first] == UNDISCOVERED)
                {
                    status[it->first] = DISCOVERED;
                    parent[it->first] = v;    
                    q.push(it->first);
                }
                
            }
                  
            if(!q.empty()) cout << ", ";     
                    
        }
    
        cout << endl;
    }
    
    void shortest_path_unweighted(const T & v1, const T & v2)
    {
        Vertex * start = find(v1);
        Vertex * end = find(v2);
        if(start == NULL || end == NULL) return;
    
        static const int UNDISCOVERED = 0;
        static const int DISCOVERED = 1;
        static const int PROCESSED = 2;
    
        map<Vertex *, int> status;
        map<Vertex *, Vertex *> parent;
    
        for(typename List::iterator it = V.begin(); it != V.end(); it++)
        {
            status[*it] = UNDISCOVERED;
            parent[*it] = NULL;
        }
        
        
        queue<Vertex *> q;
        q.push(start);
        status[start] = DISCOVERED;
        
        while(!q.empty())
        {
            Vertex *v = q.front();    
            q.pop();
           
            status[v] = PROCESSED;
        
            for(typename ListPair::iterator it = v->V.begin(); it != v->V.end(); it++)
            {
                if(status[it->first] == UNDISCOVERED)
                {
                    status[it->first] = DISCOVERED;
                    parent[it->first] = v; 
                    if(it->first == end) goto outloop;
                    q.push(it->first);
                    
                }
                
            }    
                    
        }
    
        outloop:
    
        if(parent[end] == NULL) cout << "No path" << endl;
        while(end != NULL)
        {
            cout << end->value;
            if(parent[end] != NULL)
                cout << " <-- ";
            end = parent[end];
        }
        cout << endl;
        
    }
    
    
    void print()
    {
        if(V.empty()) cout << "(empty)" << endl;
    
        for(typename List::iterator it = V.begin(); it != V.end(); it++)
        {
            cout << (*it)->value << " --> ";
            for(typename ListPair::iterator jt = (*it)->V.begin(); jt != (*it)->V.end(); jt++)
                cout << "[" << jt->first->value << ", " << jt->second << "]  ";
            
            cout << endl;
        }
    
    
    }
    
};

int main(int argc, char *argv[])
{

    ListWeightedGraph<string, int> g;

    string cmd;

    ifstream in;

    if(argc > 1) in.open(argv[1]);

    if(!in.is_open())
                cerr << "Error opening file." << endl;

    while(1)
    {    
        if(in.is_open())
        {
            in >> cmd;
            if(in.eof())
            {
                in.close();
                continue;
            }
        }
        else
        {
            cout << "> ";
            cin >> cmd;
            if(cin.eof()) break;
        }
            
//        cout << "CMD = " << cmd << endl;
    
        if(cmd == "quit" || cmd == "q" || cmd == "exit")
        {
            if(in.is_open())
            {
                cerr << "The \'quit\' command in a script file is not supported." << endl;
                continue;
            }
                
            break;
        }
    
        if(cmd == "insert" || cmd == "ins" || cmd == "i")
        {                 
//            cout << "INSERT" << endl;
            string value;
        
            if(in.is_open())
            {
                in >> value;
                in.ignore(MAX_CMD_LENGTH, '\n');
            }
            else
            {
                cin >> value;
                cin.ignore(MAX_CMD_LENGTH, '\n');
            }
            
            g.insert(value);
            
            continue;
        }
    
        if(cmd == "connect" || cmd == "con" || cmd == "c")
        {
//            cout << "CONNECT" << endl;
            int w;
            string v1, v2;
            if(in.is_open())
            {
                in >> v1;
                in >> v2;
                in >> w;
                in.ignore(MAX_CMD_LENGTH, '\n');
            }
            else
            {
                cin >> v1;
                cin >> v2;
                cin >> w;
                cin.ignore(MAX_CMD_LENGTH, '\n');
            }
            
            g.insert(v1, v2, w);
            continue;
        }
    
    
        if(cmd == "print" || cmd == "p")
        {
//            cout << "PRINT" << endl;
        
            if(in.is_open())
            {
                in.ignore(MAX_CMD_LENGTH, '\n');
            }
            else
            {
                cin.ignore(MAX_CMD_LENGTH, '\n');
            }
             
            g.print();
            continue;
        }

        if(cmd == "file")
        {
            if(in.is_open())
            {
                cerr << "The \'file\' command in a script file is not supported." << endl;
                continue;
            }
        
            string fname;
            cin >> fname;
            cin.ignore(MAX_CMD_LENGTH, '\n');
            
            in.open(fname.c_str());            
        
            if(!in.is_open())
                cerr << "Error opening file." << endl;
            
            continue;
        }
    
        if(cmd == "bfs")
        {
            string value;
        
            if(in.is_open())
            {
                in >> value;
                in.ignore(MAX_CMD_LENGTH, '\n');
            }
            else
            {
                cin >> value;
                cin.ignore(MAX_CMD_LENGTH, '\n');
            }
             
            g.BFS(value);
            continue;
        }

        if(cmd == "dfs")
        {
            string value;
        
            if(in.is_open())
            {
                in >> value;
                in.ignore(MAX_CMD_LENGTH, '\n');
            }
            else
            {
                cin >> value;
                cin.ignore(MAX_CMD_LENGTH, '\n');
            }
             
            g.DFS(value);
            continue;
        }

        if(cmd == "spu")
        {
            string v1;
            string v2;
            if(in.is_open())
            {
                in >> v1;
                in >> v2;
                in.ignore(MAX_CMD_LENGTH, '\n');
            }
            else
            {
                cin >> v1;
                cin >> v2;
                cin.ignore(MAX_CMD_LENGTH, '\n');
            }
             
            g.shortest_path_unweighted(v1, v2);
            continue;
        }
    
    }
        
    return 0;

}

