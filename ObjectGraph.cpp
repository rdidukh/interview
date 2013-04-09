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

    int _size;
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

    T get(int index)
    {
        if(V[index] == NULL) return 0;
        
        return V[index]->value;
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

    bool insert(const T& value)
    {
        if(find(value) != EMPTY) return false;
        Vertex * v = new Vertex();
        v->value = value;      
        bool ret = insert(v);
        if(!ret) delete v;
        return ret;
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
    
    template<typename A, typename B = int>
    class ProcessGraph
    {
        Graph<A, B> &g;    
            
        public:

       // struct GraphData

        ProcessGraph(Graph &graph): g(graph) {}
        virtual void start() {}        
        virtual void end() {}        
                
        virtual void preprocess(int vertex) {}
        virtual void process(int vertex) {}

        virtual void found(int from, int to, int weight) {}
        virtual void undiscovered(int from, int to, int weight) {}
        virtual void discovered(int from, int to, int weight) {}
        virtual void processed(int from, int to, int weight) {}
    };

    template<typename TYPE, typename WEIGHT>
    bool BFS(const T& value, ProcessGraph<TYPE, WEIGHT> & pg)
    {
        int start = find(value);
        if(start == EMPTY) return false;
  
        vector<int> status(V.size(), UNDISCOVERED);       
        
        pg.start();

        queue<int> q;
        q.push(start);            
            
        status[start] = DISCOVERED;
        
        while(!q.empty())
        {
            int v = q.front();
            q.pop();
                        
            pg.preprocess(v);
            
            for(typename list<Edge *>::iterator jt = V[v]->nb.begin(); jt != V[v]->nb.end(); jt++)
            {
                int y = (*jt)->vertex;
                pg.found(v, y, (*jt)->weight);
                
                if(status[y] == UNDISCOVERED)
                {
                    pg.undiscovered(v, y, (*jt)->weight);
                    status[y] = DISCOVERED;
                    q.push(y);
                }
                if(status[y] == DISCOVERED)
                {
                    pg.discovered(v, y, (*jt)->weight);        
                }
                if(status[y] == PROCESSED)
                {
                    pg.processed(v, y, (*jt)->weight);        
                }

            }

            pg.process(v);

            status[v] = PROCESSED;
        }
    
        pg.end();
        
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
class ProcessGraphPrint: public Graph::ProcessGraph<T, W>
{
    virtual void process(int vertex)
    {
        cout << g.get(vertex) << ", ";    
    }

    virtual void end()
    {
        cout << endl;
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
             
            ProcessGraphPrint pg(g);
    
            g.BFS(value, pg);
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

