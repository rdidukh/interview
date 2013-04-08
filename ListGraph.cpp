template<typename T, typename W = int>
class ListWeightedGraph
{
    unsigned max_size;  

    struct Edge 
    {
        int y;
        W weight;
        Edge *next;    
    };

    Edge * V;
    T * value;
    
    public:

    ListWeightedGraph(): ListWeightedGraph(100) {}

    ListWeightedGraph(unsigned size)
    {
        max_size = size;
        V = new Edge[size];
        T = new T[size];
    }

    ~ListWeightedGraph()
    {
        // delete all edges;
        delete[] V;
        delete[] T;
    }

};
