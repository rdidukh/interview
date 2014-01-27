#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std;

struct Word
{
    string word;
    vector<int> nb;
    int p;
    bool discovered;
};

void die(string str)
{
    cout << str << endl;
    exit(1);
}

bool neighbours(const string& first, const string& second)
{
    size_t flen = first.length();
    size_t slen = second.length();

    if(flen != slen) die("Different lengths of strings.");

    int diff = 0;

    for(int i = 0; i < flen; i++)
    {
        if(first[i] != second[i]) 
        {
            diff++;
            if(diff > 1) return false;
        }
    
    }

    if(diff == 0) die("Two identical strings found.");

    return true;
}

void BFS(int start, int iend, queue<int>& q)
{ 
    

}

int main(int argc, char* argv[])
{
    int N;

    if(argc != 4) die("word_path <dictionary file> <start word> <end word>");
   
    ifstream file;

    file.open(argv[1]);

    if(!file.is_open()) die("Error opening file.");

    string start(argv[2]);
    string end(argv[3]);

    file >> N;

    Word * words = new Word[N];

    int istart = -1;
    int iend = -1;

    for(int i = 0; i < N; i++)
    {
        file >> words[i].word;
        if(file.eof()) die("EOF!");
        words[i].discovered = false;
        words[i].p = -1;
        if(words[i].word == start) istart = i;
        if(words[i].word == end) iend = i;
    }
    
    if(istart == -1) die("Start word not found.");
    if(iend == -1) die("End word not found.");
    
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
        {
            if(i == j) continue;
  
            cout << "(" << words[i].word << ", " << words[j].word << ") = ";
            if(neighbours(words[i].word, words[j].word))
            {
                cout << "yes" << endl;
                words[i].nb.push_back(j);
            }             
            else
            {
                cout << "no" << endl;
            }                         
        }
      
      
    queue<int> q;
    words[istart].discovered = true;
    q.push(istart);

    while(!q.empty())
    {
        int v = q.front();
        q.pop();

        cout << "Vertex " << v << ": " << words[v].word << endl;    
    
        for(vector<int>::iterator i = words[v].nb.begin(); i != words[v].nb.end(); i++)
        {
            cout << "  NB: " << *i << ": " << words[*i].word;
        
            if(*i == iend)
            {
                cout << " (end)" << endl;
                words[*i].p = v;
                goto end_label;
            }
        
            if(!words[*i].discovered)
            {
                cout << " *" << endl;
                words[*i].p = v;
                words[*i].discovered = true;
                q.push(*i);
            }
            
            cout << endl;
            
        }
    }

    end_label:

    if(words[iend].p == -1) 
    {
        cout << "No path between " << start << " and " << end << endl;
        exit(0);
    }
    
    
    int next = iend;
    while(words[next].p != -1)
    {
    
        cout << words[next].word << " <-- ";
        next = words[next].p;
    }    
    cout << words[next].word << endl;
    
    delete[] words;
    file.close();
}

