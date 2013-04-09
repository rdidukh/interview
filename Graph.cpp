#include <list>
#include <vector>
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

template<typename T, typename W>
class ProcessGraph;

template <typename T, typename W = int>
class Graph
{
    static const int UNDISCOVERED = 0;
    static const int DISCOVERED = 1;
    static const int PROCESSED = 2;
    static const int EMPTY = -1;

    struct Vertex;

    struct Edge
    {
        int vertex;
        W weight;
    };

    struct Vertex
    {
        list<Edge *> nb; /* neighbours */
        T value;         /* value */
    };

    unsigned _size;
    vector<Vertex *> V;

    int findEmpty()
    {
        for(int i = 0; i < V.size(); i++)
            if(V[i] == NULL) return i;
        
        return EMPTY;
    }

    int find(const T& value)
    {    
        int c = 0;
        for(int i = 0; i < V.size(); i++)
        {
            if(V[i] == NULL) continue;
            if(V[i]->value == value) return i;
            if(++c == _size) return EMPTY;
        }

        return EMPTY;
    }
    
    bool connect(int from, int to, W weight)
    {
        if(from == EMPTY || to == EMPTY) return false;
        Edge *e = new Edge();
        e->vertex = to;
        e->weight = weight;
        V[from]->nb.push_back(e);
        return true;
    }



    bool insert(Vertex * vertex)
    {
        int i = findEmpty();       
        if(i == EMPTY) return false; 
        V[i] = vertex;
        _size++;
        return true;
    }

    public:
    
    Graph(const unsigned size): V(size, (Vertex *)NULL)
    {
        _size = 0;
    }

    int max_size()
    {
        return V.size();
    }

    unsigned size()
    {
        return _size;
    }

    bool insert(const T& value)
    {
        if(find(value) != EMPTY) return false;
        Vertex * v = new Vertex();
        v->value = value;      
        bool ret = insert(v);
        if(!ret) delete v;
        return ret;
    }
    
    T value(int index)
    {
        if(V[index] == NULL) return 0;
        
        return V[index]->value;
    }

    int index(const T & value)
    {
        return find(value);        
    }

    bool connected(const T& from, const T& to)
    {
        int vfrom = find(from);
        int vto = find(to);
        if(vfrom == EMPTY || vto == EMPTY) return false;    
        for(typename list<Edge *>::iterator jt = V[vfrom]->nb.begin(); jt != V[vfrom]->nb.end(); jt++)
            if((*jt)->vertex == vto) return true;
                
        return false;
    }

    bool neighbours(const T& value, map<T, W>& nb)
    {
        int vfrom = find(value);
        if(vfrom == EMPTY) return false;

        nb.clear();

        for(typename list<Edge *>::iterator jt = V[vfrom]->nb.begin(); jt != V[vfrom]->nb.end(); jt++)
            nb[V[(*jt)->vertex]] = (*jt)->weight;
    }

    W weight(const T& from, const T& to)
    {
        int vfrom = find(from);
        int vto = find(to);
        if(vfrom == EMPTY || vto == EMPTY) return 0;     

        for(typename list<Edge *>::iterator jt = V[vfrom]->nb.begin(); jt != V[vfrom]->nb.end(); jt++)
            if((*jt)->vertex == vto) return (*jt)->weight;

        return 0;
    }

    /* Insert edge with weight 'weight' from 'from' vertex to 'to' vertex. */
    bool connect(const T& from, const T& to, const W& weight)
    {
        int vfrom = find(from);     
        int vto = find(to);
        
        return connect(vfrom, vto, weight);
    }  
  
    bool BFS(const T& value, ProcessGraph<T, W> & pg)
    {

        int start = find(value);

        if(start == EMPTY) return false;
  
        vector<int> status(V.size(), (int)UNDISCOVERED);       
        vector<int> parent(V.size(), (int)EMPTY);        

        pg.start();

        queue<int> q;
        q.push(start);            
            
        status[start] = DISCOVERED;
        pg.first(start, status);        

        while(!q.empty())
        {
            int v = q.front();
            q.pop();
                        
            pg.preprocess(v, status);
            
            for(typename list<Edge *>::iterator jt = V[v]->nb.begin(); jt != V[v]->nb.end(); jt++)
            {
                int y = (*jt)->vertex;

                pg.found(v, y, status);

                if(status[y] == UNDISCOVERED)
                {
                    parent[y] = v;
                    status[y] = DISCOVERED;
                    if(!pg.undiscovered(v, y, status)) goto _end; 
                    q.push(y);
                }
                if(status[y] == DISCOVERED)
                {
                    pg.discovered(v, y, status);        
                }
                if(status[y] == PROCESSED)
                {
                    pg.processed(v, y, status);        
                }
            }

            if(q.empty())
            {
                pg.last(v, status);
            }
            else
            {
                pg.process(v, status);
            }

            status[v] = PROCESSED;
        }
    
        _end:

        pg.end();
        return true;
    }

    void print()
    {
        if(_size == 0) 
        {
            cout << "(empty)" << endl;
            return;
        }
        int c = 0;
        for(int i = 0; i < V.size(); i++)
        {
            if(V[i] == NULL) continue;
            cout << V[i]->value << " --> ";
            for(typename list<Edge *>::iterator jt = V[i]->nb.begin(); jt != V[i]->nb.end(); jt++)
                cout << "[\'" << V[(*jt)->vertex]->value << "\', " << (*jt)->weight << "] ";
            cout << endl;
            if(++c == _size) return;
        }  
    }
    
};


template<typename T, typename W>
class ProcessGraph
{
    protected: 
    
    ProcessGraph() {}        

    public:

    virtual bool start() {}        
    virtual void end() {}        
            
    virtual bool preprocess(int vertex, vector<int> & status) {}
    virtual bool process(int vertex, vector<int> & status) {}
    virtual bool last(int vertex, vector<int> & status) {}
    virtual bool first(int vertex, vector<int> & status) {}
    
    virtual bool found(int from, int to, vector<int> & status) {}
    virtual bool undiscovered(int from, int to, vector<int> & status) { return true;}
    virtual bool discovered(int from, int to, vector<int> & status) {}
    virtual bool processed(int from, int to, vector<int> & status) {}
};


template<typename T, typename W>
class ProcessGraphPrint: public ProcessGraph<T, W>
{ 
    Graph<T, W> * g;

    public:

    virtual bool process(int vertex, vector<int> & status)
    {
        cout << g->value(vertex) << ", ";    
    }

    virtual bool last(int vertex, vector<int> & status)
    {
        cout << g->value(vertex);    
    }

    virtual void end()
    {
        cout << endl;
    }

    ProcessGraphPrint(Graph<T, W> *graph): g(graph) {}

};



template<typename T, typename W>
class ProcessGraphShortestPath: public ProcessGraph<T, W>
{
    Graph<T, W> * g;

    vector<int> parents;

    int from;
    int to;

    static const int EMPTY = -1; 

    public:

    virtual bool undiscovered(int from, int to, vector<int> & status)
    {
        parents[to] = from;
        if(this->to == to) return false;   
        return true;
    }

    virtual void end()
    {
        if(parents[to] == EMPTY)
        {
            cout << "No path from \'" << g->value(from) << "\' to \'" << g->value(to) << "\'." << endl;
            return;
        }

        cout << "from = " << from << endl;
        cout << "to = " << to << endl;
        cout << "parents[to] = " << parents[to] << endl;

        int p = to;
        while(p != from) 
        {
            cout << g->value(p) << " <-- ";
            p = parents[p];
        }

        cout << g->value(from) << endl;

    }

    ProcessGraphShortestPath(Graph<T, W> *graph, const T& from, const T& to): g(graph), parents(g->max_size(), EMPTY)
    {
        this->from = g->index(from);
        this->to = g->index(to);       
    }
};



int main(int argc, char *argv[])
{

    Graph<string, int> g(100);

    string cmd;

    ifstream in;

    if(argc > 1)
    {
        in.open(argv[1]);
        if(!in.is_open())
            cerr << "Error opening file." << endl;
    }

    

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
            
    
        if(cmd == "quit" || cmd == "q" || cmd == "exit")
        {
            if(in.is_open())
            {
                cerr << "\'QUIT\' command in a script file is not supported." << endl;
                continue;
            }
                
            break;
        }
    
        if(cmd == "insert" || cmd == "ins" || cmd == "i")
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
            
            if(!g.insert(value)) cout << "Insertion failed." << endl;
            
            continue;
        }
    
        if(cmd == "connect" || cmd == "con" || cmd == "c")
        {
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
            
            if(!g.connect(v1, v2, w))
            {
                cout << "Connection failed." << endl;
            }
            continue;
        }
    
    
        if(cmd == "print" || cmd == "p")
        {   
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
                cerr << "\'FILE\' command in a script file is not supported." << endl;
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
             
            ProcessGraphPrint<string, int> pg(&g);
    
            if(!g.BFS(value, pg))
            {
                cout << "BFS failed." << endl;
            }
            continue;
        }


        if(cmd == "spu")
        {
            string from;
            string to;
        
            if(in.is_open())
            {
                in >> from;
                in >> to;
                in.ignore(MAX_CMD_LENGTH, '\n');
            }
            else
            {
                cin >> from;
                cin >> to;
                cin.ignore(MAX_CMD_LENGTH, '\n');
            }
             
            ProcessGraphShortestPath<string, int> pg(&g, from, to);
    
            if(!g.BFS(from, pg))
            {
                cout << "SPU failed." << endl;
            }
            continue;
        }

/*    
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
*/
/*
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

*/
/*
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
*/    

        cout << "Unknown command." << endl;
        if(in.is_open())
        {
            in.ignore(MAX_CMD_LENGTH, '\n');
        }
        else
        {
            cin.ignore(MAX_CMD_LENGTH, '\n');
        }

    }
        
    return 0;

}

