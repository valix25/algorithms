#include <iostream>
#include <stdlib.h>
#include <limits.h>
using namespace std;


class Digraph{

private:
   const int V; // number of vertexes
   int E; // number of edges
   int **mat_adj;
   int minKey(int [], bool []);
   void printMST(int []);
public:
   Digraph(int);
   ~Digraph();
   int V_number();
   int E_number();
   void addEdge(int,int,int);
   void printDigraph();
   void primMST();

};

Digraph::Digraph(int v):V(v){
    // memory allocation for the adjacency matrix
    E = 0;
    mat_adj = new int*[v];
    for(int i = 0; i < v; i++){
        mat_adj[i] = new int[v];
    }

    for(int i=0; i < v; i++)
       for(int j=0; j < v; j++)
          mat_adj[i][j] = 0;
}

Digraph::~Digraph(){
    for(int i = 0; i < V; i++){
        delete[] mat_adj[i];
    }
    delete[] mat_adj;
}

int Digraph::V_number(){
    return V;
}

int Digraph::E_number(){
    return E;
}

void Digraph::addEdge(int u, int v, int w){
   // assuming u and v are legit nodes
   // also creating an bidirected connection between the nodes
   // in the lecture notes an undirected graph was mentioned
   // adding weight to the edge between the nodes
   mat_adj[u][v] = w;
   mat_adj[v][u] = w;
   E++;
}

// finding the vertex with minimum key value,
// which is not included in MST
int Digraph::minKey(int key[],bool mstSet[]){

   // initialize min
   int min = INT_MAX;
   int min_index;

   for(int i=0; i<V; i++)
      if(mstSet[i] == false && key[i] < min){
         min = key[i];
         min_index = i;
      }

   return min_index;
}

void Digraph::printMST(int parent[]){
   cout<<"Minimum Spanning Tree\n";
   cout<<"Edge    Weight\n";
   for(int i=1; i<V; i++)
      cout<<parent[i]<<" - "<<i<<" --- "<<mat_adj[i][parent[i]]<<"\n";
}

void Digraph::primMST(){

    int parent[V]; // store the build MST
    int key[V]; // key values to pick the minimum edge
    bool mstSet[V]; //to keep track of the vertices already in MST

    // initialization
    for(int i=0; i < V; i++){
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1; //root

    for(int counter = 0; counter < V-1; counter++) // MST will have all vertices
    {
        int u = minKey(key,mstSet); // get the minimum key vertex from the set

        mstSet[u] = true; // add to the set

        for(int v=0;v<V;v++)
          if(mat_adj[u][v] != 0 && mstSet[v] == false && mat_adj[u][v] < key[v]){
             parent[v] = u;
             key[v] = mat_adj[u][v];
          }

    }

   printMST(parent);
}


void Digraph::printDigraph(){
    cout<<"Digraph info: \n";
    cout<<V<<" vertexes, "<<E<<" edges.\n";
    for(int i = 0; i < V; i++){
       cout<<"Vertex "<<i<<": ";
       for(int j = 0; j < V; j++){
           if(mat_adj[i][j]) cout<<j<<" ";
       }
       cout<<"\n";
    }
}

int main()
{
    Digraph G(8); // we'll take the example from the slides

    G.addEdge(1,3,12);
    G.addEdge(1,2,6);
    G.addEdge(2,3,5);
    G.addEdge(3,4,9);
    G.addEdge(2,5,14);
    G.addEdge(2,6,8);
    G.addEdge(5,6,3);
    G.addEdge(3,0,7);
    G.addEdge(0,6,10);
    G.addEdge(0,7,15);
    G.printDigraph();

    cout<<"\n";
    G.primMST();
    return 0;
}


/**
Algorithm:
1. mstSet keeps track of vertices already in MST
2. create a key array which assigns to each vertex a key value.
Initialize it with infinite and key[0] = 0(considerign vertex 0 as the source)
Initialize mstSet array to false.
3. while mstSet doesn't have all the vertices
3.1. -- get minimum key vertex u not included in MST
3.2. -- update mstSet (add the vertex to MST)
3.3. -- for each adjacent node v to u update their key values as
        weight u-v.
*/
