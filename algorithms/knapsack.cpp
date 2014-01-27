#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

struct Item
{
    string name;
    int weight;
    int value;
};

Item * item;

void die(string str)
{
    cout << str << endl;
    exit(1);
}

int max(int a, int b)
{
    return a>b?a:b;
}

int main(int argc, char * argv[])
{

    unsigned W; /* knapsack size */
    unsigned N; /* Number of items */

    if(argc < 2) die("usage: ./knapsack knapsack.txt");
    
    ifstream file;

    file.open(argv[1]);

    if(!file.is_open()) die("ERROR: Can not open the file.");

    file >> W;

    if(W < 0) die("ERROR: bad file format(W).");

    file >> N;
        
    if(N < 1) die("ERROR: bad file format(N).");

    item = new Item[N];
    
    for(int i = 0; i < N; i++)
    {
        file >> item[i].name;
        file >> item[i].weight;
        file >> item[i].value;
        if(file.eof()) die("ERROR: bad file format(EOF).");
    }
    
    file.close();    

    int **A;
    
    A = new int*[W+1];
    
    for(int i = 0; i < W+1; i++)
        A[i] = new int[N];



   for(int i = 0; i < N; i++)
   {
        for(int j = 0; j <= W; j++)
        { 
            if(i == 0)
            {
                if(j < item[i].weight)
                    A[j][i] = 0;
                else    
                    A[j][i] = item[i].value;
            }
            else
            {
                if(j < item[i].weight)
                    A[j][i] = A[j][i-1];
                else    
                    A[j][i] = max(A[j][i-1], A[j-item[i].weight][i-1] + item[i].value);
            }
            //cout << "A[" << j << "][" << i << "] = " << A[j][i] << endl;
        }

    }

    for(int j = 0; j <= W; j++)
    {
        for(int i = 0; i < N; i++)
        {   
            cout << A[j][i] << " ";
        }
        cout << endl;
    }

    for(int i = 0; i < W+1; i++)
        delete[] A[i];

    delete[] A;

    delete[] item;




}

